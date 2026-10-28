#ifndef FAMAK_CONFIG_H_
#define FAMAK_CONFIG_H_

#include <stdint.h>
#include <stdbool.h>
#include "tusb.h"

/*
 * ============================================================================
 * Keysatron FAMAK Multi-Layer Configuration
 * ============================================================================
 * This file contains the complete multi-layer keyboard mappings for Keysatron.
 * It provides two host profiles:
 *   1. FAMAK_PROFILE_LINUX   - Mimics the Linux `keyd` daemon configuration
 *                              (default, using Meta/Super shortcuts & Linux scancodes)
 *   2. FAMAK_PROFILE_WINDOWS - Mimics AutoHotkey Windows configuration
 *                              (using Alt shortcuts & Windows scancodes)
 *
 * Layers:
 *   - Normal (Base)
 *   - Sym    (Hold # / SC02B)
 *   - Nav    (Hold AltGr / SC138)
 *   - Exo    (Hold Tab / SC00F, or Nav+#, or Sym+AltGr)
 *   - Shift  (Hold + / SC01B, Space sends '?')
 * ============================================================================
 */

typedef struct {
  uint8_t keycode;   // USB HID keycode (0 if modifier-only or unmapped)
  uint8_t modifiers; // Forced modifiers (KEYBOARD_MODIFIER_* bitmask)
  uint8_t flags;     // FLAG_NONE, FLAG_PASS_MODS, FLAG_NOOP
} map_entry_t;

#define FLAG_NONE       0x00
#define FLAG_PASS_MODS  0x01 // Pass user Shift, Ctrl, Alt, GUI
#define FLAG_NOOP       0x02 // Inactive / drop key in this layer

typedef enum {
  FAMAK_PROFILE_LINUX = 0,   // keyd configuration (Default)
  FAMAK_PROFILE_WINDOWS = 1, // AutoHotkey configuration
  FAMAK_PROFILE_COUNT
} famak_profile_t;

typedef enum {
  FAMAK_LAYER_NORMAL = 0,
  FAMAK_LAYER_SYM    = 1,
  FAMAK_LAYER_NAV    = 2,
  FAMAK_LAYER_EXO    = 3,
  FAMAK_LAYER_COUNT
} famak_layer_t;

// Profiles x Layers x 256 keys lookup table
extern const map_entry_t famak_profiles[FAMAK_PROFILE_COUNT][FAMAK_LAYER_COUNT][256];

#endif // FAMAK_CONFIG_H_
