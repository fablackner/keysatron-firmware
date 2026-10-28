#include "layout_engine.h"
#include <string.h>

static famak_profile_t current_profile = FAMAK_PROFILE_LINUX; // Default: Linux (keyd)
static famak_layer_t   current_layer   = FAMAK_LAYER_NORMAL;
static bool            keymap_is_active = true;
static bool            profile_switch_latched = false;

void layout_engine_init(void) {
  current_profile = FAMAK_PROFILE_LINUX;
  current_layer   = FAMAK_LAYER_NORMAL;
  keymap_is_active = true;
  profile_switch_latched = false;
}

bool layout_is_active(void) {
  return keymap_is_active;
}

void layout_set_active(bool active) {
  keymap_is_active = active;
}

famak_layer_t layout_get_active_layer(void) {
  return current_layer;
}

famak_profile_t layout_get_profile(void) {
  return current_profile;
}

void layout_set_profile(famak_profile_t profile) {
  if (profile < FAMAK_PROFILE_COUNT) {
    current_profile = profile;
  }
}

famak_profile_t layout_cycle_profile(void) {
  current_profile = (famak_profile_t)((current_profile + 1) % FAMAK_PROFILE_COUNT);
  return current_profile;
}

layout_event_t layout_process_report(const uint8_t in_modifier, const uint8_t in_keys[6],
                                     uint8_t* out_modifier, uint8_t out_keys[6]) {
  layout_event_t event = LAYOUT_EVENT_NONE;

  // 1. Hotkey checks:
  // - Win + Escape    (#SC001): Stop keymap (raw passthrough)
  // - Win + Backspace (#SC00E): Start keymap (FAMAK active)
  // - Win + Enter     (Switch Profile: Linux <-> Windows)
  bool win_held = (in_modifier & (KEYBOARD_MODIFIER_LEFTGUI | KEYBOARD_MODIFIER_RIGHTGUI)) != 0;
  bool enter_pressed = false;

  if (win_held) {
    for (int i = 0; i < 6; i++) {
      uint8_t k = in_keys[i];
      if (k == HID_KEY_ESCAPE) { // Win + Esc
        if (keymap_is_active) {
          keymap_is_active = false;
          event = LAYOUT_EVENT_ACTIVATION_CHANGED;
        }
      } else if (k == HID_KEY_BACKSPACE) { // Win + Backspace
        if (!keymap_is_active) {
          keymap_is_active = true;
          event = LAYOUT_EVENT_ACTIVATION_CHANGED;
        }
      } else if (k == HID_KEY_ENTER || k == HID_KEY_KEYPAD_ENTER) {
        enter_pressed = true;
      }
    }
  }

  // Edge-triggered profile switch on Win + Enter
  if (enter_pressed) {
    if (!profile_switch_latched) {
      layout_cycle_profile();
      profile_switch_latched = true;
      event = LAYOUT_EVENT_PROFILE_CHANGED;
    }
  } else {
    profile_switch_latched = false;
  }

  // If keymap is stopped, pass through raw keys transparently
  if (!keymap_is_active) {
    *out_modifier = in_modifier;
    for (int i = 0; i < 6; i++) {
      out_keys[i] = in_keys[i];
    }
    return event;
  }

  // 2. Scan for layer hold keys
  bool exo_pressed = false;      // SC00F (Tab)
  bool sym_pressed = false;      // SC02B (# / \)
  bool nav_pressed = false;      // SC138 (AltGr / RAlt)
  bool shift_pressed = false;    // SC01B (+)
  bool capslock_pressed = false; // SC03A (CapsLock -> LeftControl)

  for (int i = 0; i < 6; i++) {
    uint8_t k = in_keys[i];
    if (k == HID_KEY_TAB)                                 exo_pressed = true;
    if (k == HID_KEY_EUROPE_1 || k == HID_KEY_BACKSLASH) sym_pressed = true;
    if (k == HID_KEY_BRACKET_RIGHT)                       shift_pressed = true;
    if (k == HID_KEY_CAPS_LOCK)                           capslock_pressed = true;
  }
  if (in_modifier & KEYBOARD_MODIFIER_RIGHTALT) {
    nav_pressed = true;
  }

  // 3. Resolve active layer:
  // - Holding Tab (Exo): if # also held -> Sym, else Exo
  // - Holding Nav: if # also held -> Exo, else Nav
  // - Holding Sym: if Nav/AltGr also held -> Exo, else Sym
  if (exo_pressed) {
    if (sym_pressed) {
      current_layer = FAMAK_LAYER_SYM;
    } else {
      current_layer = FAMAK_LAYER_EXO;
    }
  } else if (nav_pressed) {
    if (sym_pressed) {
      current_layer = FAMAK_LAYER_EXO;
    } else {
      current_layer = FAMAK_LAYER_NAV;
    }
  } else if (sym_pressed) {
    if (nav_pressed) {
      current_layer = FAMAK_LAYER_EXO;
    } else {
      current_layer = FAMAK_LAYER_SYM;
    }
  } else {
    current_layer = FAMAK_LAYER_NORMAL;
  }

  // Initialize output modifiers
  uint8_t active_mods = in_modifier;
  if (nav_pressed) {
    // Strip RightAlt if it's consumed as Nav layer trigger
    active_mods &= ~KEYBOARD_MODIFIER_RIGHTALT;
  }
  if (capslock_pressed) {
    active_mods |= KEYBOARD_MODIFIER_LEFTCTRL;
  }
  if (shift_pressed) {
    active_mods |= KEYBOARD_MODIFIER_LEFTSHIFT;
  }

  // Determine user shift state
  bool user_shifted = (active_mods & (KEYBOARD_MODIFIER_LEFTSHIFT | KEYBOARD_MODIFIER_RIGHTSHIFT)) != 0;

  // 4. Process each non-layer key
  uint8_t out_idx = 0;
  uint8_t combined_forced_mods = 0;
  bool has_forced_mods = false;
  bool pass_user_mods = false;

  for (int i = 0; i < 6; i++) {
    uint8_t in_k = in_keys[i];
    if (in_k == 0) continue;

    // Skip layer-switch keys so they don't emit characters themselves
    if (in_k == HID_KEY_TAB && exo_pressed) continue;
    if ((in_k == HID_KEY_EUROPE_1 || in_k == HID_KEY_BACKSLASH) && sym_pressed) continue;
    if (in_k == HID_KEY_BRACKET_RIGHT && shift_pressed) continue;
    if (in_k == HID_KEY_CAPS_LOCK) continue;

    // Special Space key behavior in Normal layer when Shift is active:
    // SC039 (Space) with Shift -> Send, ? (Shift + ß on German layout)
    if (current_layer == FAMAK_LAYER_NORMAL && in_k == HID_KEY_SPACE && user_shifted) {
      if (out_idx < 6) {
        out_keys[out_idx++] = HID_KEY_MINUS;
        combined_forced_mods |= KEYBOARD_MODIFIER_LEFTSHIFT;
        has_forced_mods = true;
      }
      continue;
    }

    // Look up in current profile and layer table
    map_entry_t entry = famak_profiles[current_profile][current_layer][in_k];

    // If entry is marked NOOP, drop it
    if (entry.flags & FLAG_NOOP) {
      continue;
    }

    // If entry has a mapping:
    if (entry.keycode != 0) {
      if (out_idx < 6) {
        out_keys[out_idx++] = entry.keycode;
      }
      if (entry.flags & FLAG_PASS_MODS) {
        pass_user_mods = true;
        if (entry.modifiers != 0) {
          combined_forced_mods |= entry.modifiers;
        }
      } else {
        combined_forced_mods |= entry.modifiers;
        has_forced_mods = true;
      }
    } else if (entry.modifiers != 0) {
      // Modifier-only key (e.g. N -> LeftMeta, CapsLock -> LeftCtrl, BracketRight -> RightShift)
      combined_forced_mods |= entry.modifiers;
      has_forced_mods = true;
    } else {
      // Unmapped key (Enter, Arrows, Esc, etc.) -> pass through directly
      if (out_idx < 6) {
        out_keys[out_idx++] = in_k;
      }
      pass_user_mods = true;
    }
  }

  // Clear remaining output key slots
  while (out_idx < 6) {
    out_keys[out_idx++] = 0;
  }

  // Combine modifiers:
  if (pass_user_mods) {
    *out_modifier = combined_forced_mods | active_mods;
  } else if (has_forced_mods) {
    *out_modifier = combined_forced_mods | (active_mods & (KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT | KEYBOARD_MODIFIER_LEFTGUI | KEYBOARD_MODIFIER_RIGHTGUI));
  } else {
    *out_modifier = active_mods;
  }

  return event;
}
