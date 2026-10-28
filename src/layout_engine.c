#include "layout_engine.h"
#include "tusb.h"

static layout_mode_t current_mode = LAYOUT_MODE_COLEMAK_DE;
static bool hotkey_prev_pressed = false;

// Remap lookup tables indexed by USB HID keycode (0x00 to 0x70)
// For any keycode not explicitly remapped, returns the original keycode.

// Mode 0: Colemak for German (QWERTZ) Host OS
// When the host OS is configured with German keyboard layout,
// physical scancodes are mapped to the HID keycodes that make the German OS output Colemak.
static uint8_t remap_colemak_de(uint8_t key) {
  switch (key) {
    // Row 2:
    case HID_KEY_E:             return HID_KEY_F;         // 'e' -> 'f'
    case HID_KEY_R:             return HID_KEY_P;         // 'r' -> 'p'
    case HID_KEY_T:             return HID_KEY_G;         // 't' -> 'g'
    case HID_KEY_Y:             return HID_KEY_J;         // Keycap 'Z' (pos 7) -> 'j'
    case HID_KEY_U:             return HID_KEY_L;         // 'u' -> 'l'
    case HID_KEY_I:             return HID_KEY_U;         // 'i' -> 'u'
    case HID_KEY_O:             return HID_KEY_Z;         // 'o' -> 'y' (German OS interprets HID_KEY_Z as 'y')
    case HID_KEY_P:             return HID_KEY_SEMICOLON; // 'p' -> ';' / 'ö' position

    // Row 3:
    case HID_KEY_S:             return HID_KEY_R;         // 's' -> 'r'
    case HID_KEY_D:             return HID_KEY_S;         // 'd' -> 's'
    case HID_KEY_F:             return HID_KEY_T;         // 'f' -> 't'
    case HID_KEY_G:             return HID_KEY_D;         // 'g' -> 'd'
    case HID_KEY_J:             return HID_KEY_N;         // 'j' -> 'n'
    case HID_KEY_K:             return HID_KEY_E;         // 'k' -> 'e'
    case HID_KEY_L:             return HID_KEY_I;         // 'l' -> 'i'
    case HID_KEY_SEMICOLON:     return HID_KEY_O;         // Keycap 'Ö' -> 'o'

    // Row 4:
    case HID_KEY_Z:             return HID_KEY_Y;         // Keycap 'Y' (pos 3) -> 'z' (German OS interprets HID_KEY_Y as 'z')
    case HID_KEY_N:             return HID_KEY_K;         // 'n' -> 'k'

    default:
      return key;
  }
}

// Mode 1: Standard Colemak for US Host OS
// When the host OS is configured with standard US keyboard layout,
// physical keystrokes on the German ISO keyboard produce Colemak directly.
static uint8_t remap_colemak_us(uint8_t key) {
  switch (key) {
    // Row 2:
    case HID_KEY_E:             return HID_KEY_F;
    case HID_KEY_R:             return HID_KEY_P;
    case HID_KEY_T:             return HID_KEY_G;
    case HID_KEY_Y:             return HID_KEY_J;         // Keycap 'Z' (scancode 0x1C) -> 'j'
    case HID_KEY_U:             return HID_KEY_L;
    case HID_KEY_I:             return HID_KEY_U;
    case HID_KEY_O:             return HID_KEY_Y;         // 'o' -> 'y'
    case HID_KEY_P:             return HID_KEY_SEMICOLON; // 'p' -> ';'

    // Row 3:
    case HID_KEY_S:             return HID_KEY_R;
    case HID_KEY_D:             return HID_KEY_S;
    case HID_KEY_F:             return HID_KEY_T;
    case HID_KEY_G:             return HID_KEY_D;
    case HID_KEY_J:             return HID_KEY_N;
    case HID_KEY_K:             return HID_KEY_E;
    case HID_KEY_L:             return HID_KEY_I;
    case HID_KEY_SEMICOLON:     return HID_KEY_O;         // Keycap 'Ö' (scancode 0x33) -> 'o'

    // Row 4:
    case HID_KEY_Z:             return HID_KEY_Z;         // Keycap 'Y' (scancode 0x1D) -> 'z'
    case HID_KEY_N:             return HID_KEY_K;

    default:
      return key;
  }
}

void layout_engine_init(void) {
  current_mode = LAYOUT_MODE_COLEMAK_DE;
  hotkey_prev_pressed = false;
}

layout_mode_t layout_get_mode(void) {
  return current_mode;
}

void layout_set_mode(layout_mode_t mode) {
  if (mode < LAYOUT_MODE_COUNT) {
    current_mode = mode;
  }
}

layout_mode_t layout_cycle_mode(void) {
  current_mode = (layout_mode_t)((current_mode + 1) % LAYOUT_MODE_COUNT);
  return current_mode;
}

uint8_t layout_remap_key(uint8_t keycode, layout_mode_t mode) {
  if (keycode == 0) return 0;

  switch (mode) {
    case LAYOUT_MODE_COLEMAK_DE:
      return remap_colemak_de(keycode);
    case LAYOUT_MODE_COLEMAK_US:
      return remap_colemak_us(keycode);
    case LAYOUT_MODE_PASSTHROUGH:
    default:
      return keycode;
  }
}

// Hotkey check: Ctrl + Alt + C toggles layout mode
static bool check_hotkey(uint8_t modifier, const uint8_t keys[6]) {
  bool ctrl_held = (modifier & (KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_RIGHTCTRL)) != 0;
  bool alt_held  = (modifier & (KEYBOARD_MODIFIER_LEFTALT  | KEYBOARD_MODIFIER_RIGHTALT))  != 0;

  if (ctrl_held && alt_held) {
    for (int i = 0; i < 6; i++) {
      if (keys[i] == HID_KEY_C) {
        return true;
      }
    }
  }
  return false;
}

bool layout_process_report(const uint8_t in_modifier, const uint8_t in_keys[6],
                           uint8_t* out_modifier, uint8_t out_keys[6]) {
  bool mode_changed = false;
  bool hotkey_now = check_hotkey(in_modifier, in_keys);

  if (hotkey_now && !hotkey_prev_pressed) {
    // Hotkey triggered on rising edge
    layout_cycle_mode();
    mode_changed = true;
  }
  hotkey_prev_pressed = hotkey_now;

  // Pass through modifier keys
  *out_modifier = in_modifier;

  // Remap up to 6 keycodes
  for (int i = 0; i < 6; i++) {
    if (in_keys[i] != 0) {
      out_keys[i] = layout_remap_key(in_keys[i], current_mode);
    } else {
      out_keys[i] = 0;
    }
  }

  return mode_changed;
}
