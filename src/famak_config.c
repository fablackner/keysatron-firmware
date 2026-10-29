#include "famak_config.h"

const map_entry_t famak_profiles[FAMAK_PROFILE_COUNT][FAMAK_LAYER_COUNT][256] = {
  // =========================================================================
  // PROFILE 0: LINUX (keyd layout - DEFAULT)
  // =========================================================================
  [FAMAK_PROFILE_LINUX] = {
    // -----------------------------------------------------------------------
    // LAYER 0: NORMAL (keyd [main])
    // -----------------------------------------------------------------------
    [FAMAK_LAYER_NORMAL] = {
      // Row 1 (Number row)
      [HID_KEY_1]                   = { HID_KEY_ARROW_LEFT,     KEYBOARD_MODIFIER_LEFTALT, 0 }, // 1 = A-left
      [HID_KEY_2]                   = { HID_KEY_ARROW_RIGHT,    KEYBOARD_MODIFIER_LEFTALT, 0 }, // 2 = A-right
      [HID_KEY_3]                   = { HID_KEY_Y,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // 3 = C-y
      [HID_KEY_4]                   = { HID_KEY_Z,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // 4 = C-z
      [HID_KEY_5]                   = { HID_KEY_F5,             0, 0 },                         // 5 = f5
      [HID_KEY_6]                   = { HID_KEY_F6,             0, 0 },                         // 6 = f6
      [HID_KEY_7]                   = { HID_KEY_F7,             0, 0 },                         // 7 = f7
      [HID_KEY_8]                   = { HID_KEY_F8,             0, 0 },                         // 8 = f8
      [HID_KEY_9]                   = { HID_KEY_F9,             0, 0 },                         // 9 = f9
      [HID_KEY_0]                   = { HID_KEY_PAGE_DOWN,      0, 0 },                         // 0 = pagedown
      [HID_KEY_MINUS]               = { HID_KEY_PAGE_UP,        0, 0 },                         // - = pageup (physical ß)
      [HID_KEY_EQUAL]               = { HID_KEY_B,              KEYBOARD_MODIFIER_LEFTALT | KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // = = A-S-b (physical ´)

      // Row 2
      [HID_KEY_Q]                   = { HID_KEY_Q,              0, FLAG_PASS_MODS },            // q = q
      [HID_KEY_W]                   = { HID_KEY_W,              0, FLAG_PASS_MODS },            // w = w
      [HID_KEY_E]                   = { HID_KEY_C,              0, FLAG_PASS_MODS },            // e = c
      [HID_KEY_R]                   = { HID_KEY_P,              0, FLAG_PASS_MODS },            // r = p
      [HID_KEY_T]                   = { HID_KEY_B,              0, FLAG_PASS_MODS },            // t = b
      [HID_KEY_Y]                   = { HID_KEY_VOLUME_DOWN,    0, 0 },                         // y = volumedown (physical Z key)
      [HID_KEY_U]                   = { HID_KEY_J,              0, FLAG_PASS_MODS },            // u = j
      [HID_KEY_I]                   = { HID_KEY_L,              0, FLAG_PASS_MODS },            // i = l
      [HID_KEY_O]                   = { HID_KEY_U,              0, FLAG_PASS_MODS },            // o = u
      [HID_KEY_P]                   = { HID_KEY_Z,              0, FLAG_PASS_MODS },            // p = z
      [HID_KEY_BRACKET_LEFT]        = { HID_KEY_BACKSPACE,      0, 0 },                         // [ = backspace (physical Ü)
      [HID_KEY_BRACKET_RIGHT]       = { 0,                      KEYBOARD_MODIFIER_RIGHTSHIFT, 0 }, // ] = layer(shift) (physical +)

      // Row 3
      [HID_KEY_CAPS_LOCK]           = { 0,                      KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // capslock = leftcontrol
      [HID_KEY_A]                   = { HID_KEY_A,              0, FLAG_PASS_MODS },            // a = a
      [HID_KEY_S]                   = { HID_KEY_R,              0, FLAG_PASS_MODS },            // s = r
      [HID_KEY_D]                   = { HID_KEY_S,              0, FLAG_PASS_MODS },            // d = s
      [HID_KEY_F]                   = { HID_KEY_T,              0, FLAG_PASS_MODS },            // f = t
      [HID_KEY_G]                   = { HID_KEY_G,              0, FLAG_PASS_MODS },            // g = g
      [HID_KEY_H]                   = { HID_KEY_H,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // h = C-A-h
      [HID_KEY_J]                   = { HID_KEY_M,              0, FLAG_PASS_MODS },            // j = m
      [HID_KEY_K]                   = { HID_KEY_N,              0, FLAG_PASS_MODS },            // k = n
      [HID_KEY_L]                   = { HID_KEY_E,              0, FLAG_PASS_MODS },            // l = e
      [HID_KEY_SEMICOLON]           = { HID_KEY_I,              0, FLAG_PASS_MODS },            // ; = i (physical Ö)
      [HID_KEY_APOSTROPHE]          = { HID_KEY_O,              0, FLAG_PASS_MODS },            // ' = o (physical Ä)

      // Row 4
      [HID_KEY_EUROPE_2]            = { HID_KEY_Y,              0, FLAG_PASS_MODS },            // 102nd = z / Z (physical < key)
      [HID_KEY_Z]                   = { HID_KEY_SEMICOLON,      0, FLAG_PASS_MODS },            // z = ö / Ö (physical Y key -> ö on German)
      [HID_KEY_X]                   = { HID_KEY_F,              0, FLAG_PASS_MODS },            // x = f
      [HID_KEY_C]                   = { HID_KEY_D,              0, FLAG_PASS_MODS },            // c = d
      [HID_KEY_V]                   = { HID_KEY_V,              0, FLAG_PASS_MODS },            // v = v
      [HID_KEY_B]                   = { HID_KEY_X,              0, FLAG_PASS_MODS },            // b = x
      [HID_KEY_N]                   = { 0,                      KEYBOARD_MODIFIER_LEFTGUI, 0 }, // n = leftmeta
      [HID_KEY_M]                   = { HID_KEY_K,              0, FLAG_PASS_MODS },            // m = k
      [HID_KEY_COMMA]               = { HID_KEY_H,              0, FLAG_PASS_MODS },            // , = h
      [HID_KEY_PERIOD]              = { HID_KEY_BRACKET_LEFT,   0, FLAG_PASS_MODS },            // . = ü / Ü (physical . key -> ü on German)
      [HID_KEY_SLASH]               = { HID_KEY_APOSTROPHE,     0, FLAG_PASS_MODS },            // / = ä / Ä (physical - key -> ä on German)
      [HID_KEY_SPACE]               = { HID_KEY_SPACE,          0, FLAG_PASS_MODS },
    },

    // -----------------------------------------------------------------------
    // LAYER 1: SYM (keyd [sym])
    // -----------------------------------------------------------------------
    [FAMAK_LAYER_SYM] = {
      [HID_KEY_1]                   = { HID_KEY_1,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // 1 = C-1
      [HID_KEY_2]                   = { HID_KEY_2,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // 2 = C-2
      [HID_KEY_3]                   = { HID_KEY_3,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // 3 = C-3
      [HID_KEY_4]                   = { HID_KEY_4,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // 4 = C-4
      [HID_KEY_5]                   = { HID_KEY_5,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // 5 = C-5
      [HID_KEY_6]                   = { HID_KEY_6,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // 6 = C-6
      [HID_KEY_7]                   = { HID_KEY_7,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // 7 = C-7
      [HID_KEY_8]                   = { HID_KEY_8,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // 8 = C-8
      [HID_KEY_9]                   = { HID_KEY_9,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // 9 = C-9
      [HID_KEY_0]                   = { HID_KEY_0,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // 0 = C-10 / C-0
      [HID_KEY_MINUS]               = { HID_KEY_MINUS,          KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // - = C-11
      [HID_KEY_EQUAL]               = { HID_KEY_EQUAL,          KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // = = C-12

      [HID_KEY_Q]                   = { HID_KEY_BRACKET_RIGHT,  KEYBOARD_MODIFIER_RIGHTALT, 0 }, // q = ~ (AltGr + +)
      [HID_KEY_W]                   = { HID_KEY_1,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // w = ! (Shift + 1)
      [HID_KEY_E]                   = { HID_KEY_7,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // e = / (Shift + 7)
      [HID_KEY_R]                   = { HID_KEY_EUROPE_2,       KEYBOARD_MODIFIER_RIGHTALT, 0 }, // r = | (AltGr + <)
      [HID_KEY_T]                   = { HID_KEY_6,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // t = & (Shift + 6)
      [HID_KEY_Y]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_U]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_I]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_O]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_P]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_BRACKET_LEFT]        = { 0, 0, FLAG_NOOP },
      [HID_KEY_BRACKET_RIGHT]       = { 0,                      KEYBOARD_MODIFIER_RIGHTSHIFT, 0 }, // ] = rightshift
      [HID_KEY_CAPS_LOCK]           = { 0,                      KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // capslock = leftcontrol

      [HID_KEY_A]                   = { HID_KEY_SLASH,          0, 0 },                          // a = - (physical - key)
      [HID_KEY_S]                   = { HID_KEY_BRACKET_RIGHT,  0, 0 },                          // s = + (physical + key)
      [HID_KEY_D]                   = { HID_KEY_BRACKET_RIGHT,  KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // d = * (Shift + +)
      [HID_KEY_F]                   = { HID_KEY_PERIOD,         0, 0 },                          // f = .
      [HID_KEY_G]                   = { HID_KEY_COMMA,          0, 0 },                          // g = ,
      [HID_KEY_H]                   = { 0, 0, FLAG_NOOP },                                       // h = noop
      [HID_KEY_J]                   = { HID_KEY_EQUAL,          KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // j = ` (Shift + ´)
      [HID_KEY_K]                   = { HID_KEY_MINUS,          KEYBOARD_MODIFIER_RIGHTALT, 0 }, // k = \ (AltGr + ß)
      [HID_KEY_L]                   = { HID_KEY_GRAVE,          0, 0 },                          // l = ^ (physical ^ key)
      [HID_KEY_SEMICOLON]           = { HID_KEY_EQUAL,          0, 0 },                          // ; = ´ (physical ´ key)
      [HID_KEY_APOSTROPHE]          = { HID_KEY_GRAVE,          KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // ' = ° (Shift + ^)

      [HID_KEY_EUROPE_2]            = { HID_KEY_EUROPE_2,       0, 0 },                          // 102nd = <
      [HID_KEY_Z]                   = { HID_KEY_EUROPE_1,       0, 0 },                          // z = # (physical # key)
      [HID_KEY_X]                   = { HID_KEY_EUROPE_2,       KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // x = > (Shift + <)
      [HID_KEY_C]                   = { HID_KEY_0,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // c = = (Shift + 0)
      [HID_KEY_V]                   = { HID_KEY_COMMA,          KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // v = ; (Shift + ,)
      [HID_KEY_B]                   = { HID_KEY_MINUS,          KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // b = ? (Shift + ß)
      [HID_KEY_N]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_M]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_COMMA]               = { HID_KEY_5,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // , = % (Shift + 5)
      [HID_KEY_PERIOD]              = { 0, 0, FLAG_NOOP },
      [HID_KEY_SLASH]               = { 0, 0, FLAG_NOOP },
      [HID_KEY_SPACE]               = { HID_KEY_PERIOD,         KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // space = : (Shift + .)
    },

    // -----------------------------------------------------------------------
    // LAYER 2: NAV (keyd [nav] - LINUX SHORTCUTS)
    // -----------------------------------------------------------------------
    [FAMAK_LAYER_NAV] = {
      [HID_KEY_1]                   = { HID_KEY_1,              KEYBOARD_MODIFIER_LEFTGUI, 0 }, // 1 = M-1 (Super+1)
      [HID_KEY_2]                   = { HID_KEY_2,              KEYBOARD_MODIFIER_LEFTGUI, 0 }, // 2 = M-2
      [HID_KEY_3]                   = { HID_KEY_3,              KEYBOARD_MODIFIER_LEFTGUI, 0 }, // 3 = M-3
      [HID_KEY_4]                   = { HID_KEY_4,              KEYBOARD_MODIFIER_LEFTGUI, 0 }, // 4 = M-4
      [HID_KEY_5]                   = { HID_KEY_5,              KEYBOARD_MODIFIER_LEFTGUI, 0 }, // 5 = M-5
      [HID_KEY_6]                   = { HID_KEY_6,              KEYBOARD_MODIFIER_LEFTGUI, 0 }, // 6 = M-6
      [HID_KEY_7]                   = { HID_KEY_7,              KEYBOARD_MODIFIER_LEFTGUI, 0 }, // 7 = M-7
      [HID_KEY_8]                   = { HID_KEY_8,              KEYBOARD_MODIFIER_LEFTGUI, 0 }, // 8 = M-8
      [HID_KEY_9]                   = { HID_KEY_9,              KEYBOARD_MODIFIER_LEFTGUI, 0 }, // 9 = M-9
      [HID_KEY_0]                   = { HID_KEY_0,              KEYBOARD_MODIFIER_LEFTGUI | KEYBOARD_MODIFIER_LEFTALT, 0 }, // 0 = M-A-0
      [HID_KEY_MINUS]               = { HID_KEY_1,              KEYBOARD_MODIFIER_LEFTGUI | KEYBOARD_MODIFIER_LEFTALT, 0 }, // - = M-A-1
      [HID_KEY_EQUAL]               = { HID_KEY_2,              KEYBOARD_MODIFIER_LEFTGUI | KEYBOARD_MODIFIER_LEFTALT, 0 }, // = = M-A-2
      [HID_KEY_BACKSPACE]           = { HID_KEY_F4,             KEYBOARD_MODIFIER_LEFTALT, 0 }, // backspace = A-f4

      [HID_KEY_Q]                   = { HID_KEY_W,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // q = C-A-w
      [HID_KEY_W]                   = { HID_KEY_ARROW_LEFT,     0, FLAG_PASS_MODS },            // w = left
      [HID_KEY_E]                   = { HID_KEY_ARROW_UP,       0, FLAG_PASS_MODS },            // e = up
      [HID_KEY_R]                   = { HID_KEY_ARROW_RIGHT,    0, FLAG_PASS_MODS },            // r = right
      [HID_KEY_T]                   = { HID_KEY_T,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // t = C-A-t
      [HID_KEY_Y]                   = { HID_KEY_MUTE,           0, 0 },                          // y = mute
      [HID_KEY_U]                   = { HID_KEY_F14,            0, 0 },                          // u = brightnessdown
      [HID_KEY_I]                   = { HID_KEY_F15,            0, 0 },                          // i = brightnessup
      [HID_KEY_O]                   = { HID_KEY_8,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // o = G-8 ([)
      [HID_KEY_P]                   = { HID_KEY_9,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // p = G-9 (])
      [HID_KEY_BRACKET_LEFT]        = { HID_KEY_ESCAPE,         0, FLAG_PASS_MODS },            // [ = esc
      [HID_KEY_BRACKET_RIGHT]       = { 0,                      KEYBOARD_MODIFIER_RIGHTSHIFT, 0 }, // ] = rightshift
      [HID_KEY_CAPS_LOCK]           = { 0,                      KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // capslock = leftcontrol

      [HID_KEY_A]                   = { HID_KEY_HOME,           0, FLAG_PASS_MODS },            // a = home
      [HID_KEY_S]                   = { HID_KEY_ARROW_LEFT,     KEYBOARD_MODIFIER_LEFTCTRL, FLAG_PASS_MODS }, // s = C-left
      [HID_KEY_D]                   = { HID_KEY_ARROW_DOWN,     0, FLAG_PASS_MODS },            // d = down
      [HID_KEY_F]                   = { HID_KEY_ARROW_RIGHT,    KEYBOARD_MODIFIER_LEFTCTRL, FLAG_PASS_MODS }, // f = C-right
      [HID_KEY_G]                   = { HID_KEY_END,            0, FLAG_PASS_MODS },            // g = end
      [HID_KEY_H]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_J]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_K]                   = { HID_KEY_8,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // k = S-8 (()
      [HID_KEY_L]                   = { HID_KEY_9,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // l = S-9 ())
      [HID_KEY_SEMICOLON]           = { HID_KEY_L,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ; = C-l
      [HID_KEY_APOSTROPHE]          = { HID_KEY_DELETE,         0, FLAG_PASS_MODS },            // ' = delete

      [HID_KEY_EUROPE_2]            = { HID_KEY_4,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // 102nd = S-4 ($)
      [HID_KEY_Z]                   = { HID_KEY_INSERT,         0, FLAG_PASS_MODS },            // z = insert
      [HID_KEY_X]                   = { HID_KEY_EUROPE_1,       KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // x = S-\ (') (Shift+# on German)
      [HID_KEY_C]                   = { HID_KEY_PAGE_DOWN,      KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // c = A-pagedown
      [HID_KEY_V]                   = { HID_KEY_PAGE_UP,        KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // v = A-pageup
      [HID_KEY_B]                   = { HID_KEY_2,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // b = S-2 (")
      [HID_KEY_N]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_M]                   = { HID_KEY_7,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // m = G-7 ({)
      [HID_KEY_COMMA]               = { HID_KEY_0,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // , = G-0 (})
      [HID_KEY_PERIOD]              = { 0, 0, FLAG_NOOP },
      [HID_KEY_SLASH]               = { 0, 0, FLAG_NOOP },
      [HID_KEY_SPACE]               = { HID_KEY_TAB,            0, FLAG_PASS_MODS },            // space = tab
    },

    // -----------------------------------------------------------------------
    // LAYER 3: EXO (keyd [exo] - LINUX SHORTCUTS)
    // -----------------------------------------------------------------------
    [FAMAK_LAYER_EXO] = {
      [HID_KEY_1]                   = { HID_KEY_1,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // 1 = S-C-1
      [HID_KEY_2]                   = { HID_KEY_2,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // 2 = S-C-2
      [HID_KEY_3]                   = { HID_KEY_C,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // 3 = S-C-c (Terminal Copy)
      [HID_KEY_4]                   = { HID_KEY_V,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // 4 = S-C-v (Terminal Paste)
      [HID_KEY_5]                   = { HID_KEY_F2,             0, 0 },                          // 5 = f2
      [HID_KEY_6]                   = { HID_KEY_F3,             0, 0 },                          // 6 = f3
      [HID_KEY_7]                   = { HID_KEY_F4,             0, 0 },                          // 7 = f4
      [HID_KEY_8]                   = { HID_KEY_F10,            0, 0 },                          // 8 = f10
      [HID_KEY_9]                   = { HID_KEY_F11,            0, 0 },                          // 9 = f11
      [HID_KEY_0]                   = { HID_KEY_PAGE_DOWN,      0, FLAG_PASS_MODS },            // 0 = scrolldown
      [HID_KEY_MINUS]               = { HID_KEY_PAGE_UP,        0, FLAG_PASS_MODS },            // - = scrollup
      [HID_KEY_EQUAL]               = { HID_KEY_F10,            KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // = = S-f10
      [HID_KEY_BACKSPACE]           = { HID_KEY_ESCAPE,         KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTGUI, 0 }, // backspace = C-M-esc (Ctrl+Super+Esc)

      [HID_KEY_Q]                   = { HID_KEY_ARROW_LEFT,     KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTGUI, FLAG_PASS_MODS }, // q = C-M-left (Ctrl+Super+Left)
      [HID_KEY_W]                   = { HID_KEY_ARROW_RIGHT,    KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTGUI, FLAG_PASS_MODS }, // w = C-M-right (Ctrl+Super+Right)
      [HID_KEY_E]                   = { HID_KEY_ARROW_UP,       KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // e = C-A-up
      [HID_KEY_R]                   = { HID_KEY_PAGE_UP,        KEYBOARD_MODIFIER_LEFTCTRL, FLAG_PASS_MODS }, // r = C-pageup
      [HID_KEY_T]                   = { HID_KEY_PAGE_DOWN,      KEYBOARD_MODIFIER_LEFTCTRL, FLAG_PASS_MODS }, // t = C-pagedown
      [HID_KEY_Y]                   = { HID_KEY_VOLUME_UP,      0, 0 },                          // y = volumeup
      [HID_KEY_U]                   = { HID_KEY_Q,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // u = G-q (@)
      [HID_KEY_I]                   = { HID_KEY_7,              0, FLAG_PASS_MODS },            // i = 7
      [HID_KEY_O]                   = { HID_KEY_8,              0, FLAG_PASS_MODS },            // o = 8
      [HID_KEY_P]                   = { HID_KEY_9,              0, FLAG_PASS_MODS },            // p = 9
      [HID_KEY_BRACKET_LEFT]        = { HID_KEY_BACKSPACE,      0, FLAG_PASS_MODS },            // [ = backspace
      [HID_KEY_BRACKET_RIGHT]       = { 0,                      KEYBOARD_MODIFIER_RIGHTSHIFT, 0 }, // ] = rightshift
      [HID_KEY_CAPS_LOCK]           = { 0,                      KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // capslock = leftcontrol

      [HID_KEY_A]                   = { HID_KEY_HOME,           KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // a = C-A-home
      [HID_KEY_S]                   = { HID_KEY_HOME,           KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // s = A-home
      [HID_KEY_D]                   = { HID_KEY_ARROW_DOWN,     KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // d = C-A-down
      [HID_KEY_F]                   = { HID_KEY_END,            KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // f = A-end
      [HID_KEY_G]                   = { HID_KEY_END,            KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // g = C-A-end
      [HID_KEY_H]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_J]                   = { HID_KEY_PERIOD,         0, FLAG_PASS_MODS },            // j = .
      [HID_KEY_K]                   = { HID_KEY_4,              0, FLAG_PASS_MODS },            // k = 4
      [HID_KEY_L]                   = { HID_KEY_5,              0, FLAG_PASS_MODS },            // l = 5
      [HID_KEY_SEMICOLON]           = { HID_KEY_6,              0, FLAG_PASS_MODS },            // ; = 6
      [HID_KEY_APOSTROPHE]          = { HID_KEY_0,              0, FLAG_PASS_MODS },            // ' = 0

      [HID_KEY_EUROPE_2]            = { HID_KEY_POWER,          0, 0 },                          // 102nd = sleep
      [HID_KEY_Z]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_X]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_C]                   = { HID_KEY_PAGE_DOWN,      KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // c = C-A-pagedown
      [HID_KEY_V]                   = { HID_KEY_PAGE_UP,        KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // v = C-A-pageup
      [HID_KEY_B]                   = { HID_KEY_DELETE,         0, FLAG_PASS_MODS },            // b = delete
      [HID_KEY_N]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_M]                   = { HID_KEY_1,              0, FLAG_PASS_MODS },            // m = 1
      [HID_KEY_COMMA]               = { HID_KEY_2,              0, FLAG_PASS_MODS },            // , = 2
      [HID_KEY_PERIOD]              = { HID_KEY_3,              0, FLAG_PASS_MODS },            // . = 3
      [HID_KEY_SLASH]               = { HID_KEY_MINUS,          0, FLAG_PASS_MODS },            // / = ß (HID_KEY_MINUS on German layout produces ß)
      [HID_KEY_SPACE]               = { HID_KEY_W,              KEYBOARD_MODIFIER_LEFTGUI | KEYBOARD_MODIFIER_LEFTALT, 0 }, // space = M-A-w (Super+Alt+w)
    },
  },

  // =========================================================================
  // PROFILE 1: WINDOWS (AutoHotkey layout)
  // =========================================================================
  [FAMAK_PROFILE_WINDOWS] = {
    // -----------------------------------------------------------------------
    // LAYER 0: NORMAL (Windows AHK)
    // -----------------------------------------------------------------------
    [FAMAK_LAYER_NORMAL] = {
      [HID_KEY_1]                   = { HID_KEY_ARROW_LEFT,     KEYBOARD_MODIFIER_LEFTALT, 0 }, // !{Left}
      [HID_KEY_2]                   = { HID_KEY_ARROW_RIGHT,    KEYBOARD_MODIFIER_LEFTALT, 0 }, // !{Right}
      [HID_KEY_3]                   = { HID_KEY_Z,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^y
      [HID_KEY_4]                   = { HID_KEY_Y,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^z
      [HID_KEY_5]                   = { HID_KEY_F5,             0, 0 },                         // {f5}
      [HID_KEY_6]                   = { HID_KEY_F6,             0, 0 },                         // {f6}
      [HID_KEY_7]                   = { HID_KEY_F7,             0, 0 },                         // {f7}
      [HID_KEY_8]                   = { HID_KEY_F8,             0, 0 },                         // {f8}
      [HID_KEY_9]                   = { HID_KEY_F9,             0, 0 },                         // {f9}
      [HID_KEY_0]                   = { HID_KEY_PAGE_DOWN,      0, 0 },                         // {pagedown}
      [HID_KEY_MINUS]               = { HID_KEY_PAGE_UP,        0, 0 },                         // {pageup}
      [HID_KEY_EQUAL]               = { HID_KEY_B,              KEYBOARD_MODIFIER_LEFTALT | KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // !+b

      [HID_KEY_Q]                   = { HID_KEY_Q,              0, FLAG_PASS_MODS },            // q
      [HID_KEY_W]                   = { HID_KEY_W,              0, FLAG_PASS_MODS },            // w
      [HID_KEY_E]                   = { HID_KEY_C,              0, FLAG_PASS_MODS },            // c
      [HID_KEY_R]                   = { HID_KEY_P,              0, FLAG_PASS_MODS },            // p
      [HID_KEY_T]                   = { HID_KEY_B,              0, FLAG_PASS_MODS },            // b
      [HID_KEY_Y]                   = { HID_KEY_VOLUME_DOWN,    0, 0 },                         // {volumedown}
      [HID_KEY_U]                   = { HID_KEY_J,              0, FLAG_PASS_MODS },            // j
      [HID_KEY_I]                   = { HID_KEY_L,              0, FLAG_PASS_MODS },            // l
      [HID_KEY_O]                   = { HID_KEY_U,              0, FLAG_PASS_MODS },            // u
      [HID_KEY_P]                   = { HID_KEY_Z,              0, FLAG_PASS_MODS },            // y / Y (German layout produces y for scancode Z)
      [HID_KEY_BRACKET_LEFT]        = { HID_KEY_BACKSPACE,      0, 0 },                         // {Backspace}
      [HID_KEY_BRACKET_RIGHT]       = { 0,                      KEYBOARD_MODIFIER_RIGHTSHIFT, 0 }, // Shift

      [HID_KEY_CAPS_LOCK]           = { 0,                      KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // {leftcontrol}
      [HID_KEY_A]                   = { HID_KEY_A,              0, FLAG_PASS_MODS },            // a
      [HID_KEY_S]                   = { HID_KEY_R,              0, FLAG_PASS_MODS },            // r
      [HID_KEY_D]                   = { HID_KEY_S,              0, FLAG_PASS_MODS },            // s
      [HID_KEY_F]                   = { HID_KEY_T,              0, FLAG_PASS_MODS },            // t
      [HID_KEY_G]                   = { HID_KEY_G,              0, FLAG_PASS_MODS },            // g
      [HID_KEY_H]                   = { HID_KEY_H,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!h
      [HID_KEY_J]                   = { HID_KEY_M,              0, FLAG_PASS_MODS },            // m
      [HID_KEY_K]                   = { HID_KEY_N,              0, FLAG_PASS_MODS },            // n
      [HID_KEY_L]                   = { HID_KEY_E,              0, FLAG_PASS_MODS },            // e
      [HID_KEY_SEMICOLON]           = { HID_KEY_I,              0, FLAG_PASS_MODS },            // i
      [HID_KEY_APOSTROPHE]          = { HID_KEY_O,              0, FLAG_PASS_MODS },            // o

      [HID_KEY_EUROPE_2]            = { HID_KEY_Y,              0, FLAG_PASS_MODS },            // z / Z (German layout produces z for scancode Y)
      [HID_KEY_Z]                   = { HID_KEY_SEMICOLON,      0, FLAG_PASS_MODS },            // ö / Ö (German layout produces ö for scancode ;)
      [HID_KEY_X]                   = { HID_KEY_F,              0, FLAG_PASS_MODS },            // f
      [HID_KEY_C]                   = { HID_KEY_D,              0, FLAG_PASS_MODS },            // d
      [HID_KEY_V]                   = { HID_KEY_V,              0, FLAG_PASS_MODS },            // v
      [HID_KEY_B]                   = { HID_KEY_X,              0, FLAG_PASS_MODS },            // x
      [HID_KEY_N]                   = { 0,                      KEYBOARD_MODIFIER_LEFTGUI, 0 }, // {leftmeta}
      [HID_KEY_M]                   = { HID_KEY_K,              0, FLAG_PASS_MODS },            // k
      [HID_KEY_COMMA]               = { HID_KEY_H,              0, FLAG_PASS_MODS },            // h
      [HID_KEY_PERIOD]              = { HID_KEY_BRACKET_LEFT,   0, FLAG_PASS_MODS },            // ü / Ü (German layout produces ü for scancode [)
      [HID_KEY_SLASH]               = { HID_KEY_APOSTROPHE,     0, FLAG_PASS_MODS },            // ä / Ä (German layout produces ä for scancode ')
      [HID_KEY_SPACE]               = { HID_KEY_SPACE,          0, FLAG_PASS_MODS },
    },

    // -----------------------------------------------------------------------
    // LAYER 1: SYM (Windows AHK)
    // -----------------------------------------------------------------------
    [FAMAK_LAYER_SYM] = {
      [HID_KEY_1]                   = { HID_KEY_1,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^1
      [HID_KEY_2]                   = { HID_KEY_2,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^2
      [HID_KEY_3]                   = { HID_KEY_3,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^3
      [HID_KEY_4]                   = { HID_KEY_4,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^4
      [HID_KEY_5]                   = { HID_KEY_5,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^5
      [HID_KEY_6]                   = { HID_KEY_6,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^6
      [HID_KEY_7]                   = { HID_KEY_7,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^7
      [HID_KEY_8]                   = { HID_KEY_8,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^8
      [HID_KEY_9]                   = { HID_KEY_9,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^9
      [HID_KEY_0]                   = { HID_KEY_0,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^0
      [HID_KEY_MINUS]               = { HID_KEY_MINUS,          KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^ß
      [HID_KEY_EQUAL]               = { HID_KEY_EQUAL,          KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^´

      [HID_KEY_Q]                   = { HID_KEY_BRACKET_RIGHT,  KEYBOARD_MODIFIER_RIGHTALT, 0 }, // ~
      [HID_KEY_W]                   = { HID_KEY_1,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // !
      [HID_KEY_E]                   = { HID_KEY_7,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // /
      [HID_KEY_R]                   = { HID_KEY_EUROPE_2,       KEYBOARD_MODIFIER_RIGHTALT, 0 }, // |
      [HID_KEY_T]                   = { HID_KEY_6,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // &
      [HID_KEY_Y]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_U]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_I]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_O]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_P]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_BRACKET_LEFT]        = { 0, 0, FLAG_NOOP },
      [HID_KEY_BRACKET_RIGHT]       = { 0,                      KEYBOARD_MODIFIER_RIGHTSHIFT, 0 }, // {rightshift}
      [HID_KEY_CAPS_LOCK]           = { 0,                      KEYBOARD_MODIFIER_LEFTCTRL, 0 },

      [HID_KEY_A]                   = { HID_KEY_SLASH,          0, 0 },                          // -
      [HID_KEY_S]                   = { HID_KEY_BRACKET_RIGHT,  0, 0 },                          // +
      [HID_KEY_D]                   = { HID_KEY_BRACKET_RIGHT,  KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // *
      [HID_KEY_F]                   = { HID_KEY_PERIOD,         0, 0 },                          // .
      [HID_KEY_G]                   = { HID_KEY_COMMA,          0, 0 },                          // ,
      [HID_KEY_H]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_J]                   = { HID_KEY_EQUAL,          KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // `
      [HID_KEY_K]                   = { HID_KEY_MINUS,          KEYBOARD_MODIFIER_RIGHTALT, 0 }, // \ (AltGr + ß)
      [HID_KEY_L]                   = { HID_KEY_GRAVE,          0, 0 },                          // ^
      [HID_KEY_SEMICOLON]           = { HID_KEY_EQUAL,          0, 0 },                          // ´
      [HID_KEY_APOSTROPHE]          = { HID_KEY_GRAVE,          KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // °

      [HID_KEY_EUROPE_2]            = { HID_KEY_EUROPE_2,       0, 0 },                          // <
      [HID_KEY_Z]                   = { HID_KEY_EUROPE_1,       0, 0 },                          // #
      [HID_KEY_X]                   = { HID_KEY_EUROPE_2,       KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // >
      [HID_KEY_C]                   = { HID_KEY_0,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // =
      [HID_KEY_V]                   = { HID_KEY_COMMA,          KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // ;
      [HID_KEY_B]                   = { HID_KEY_MINUS,          KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // ?
      [HID_KEY_N]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_M]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_COMMA]               = { HID_KEY_5,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // %
      [HID_KEY_PERIOD]              = { 0, 0, FLAG_NOOP },
      [HID_KEY_SLASH]               = { 0, 0, FLAG_NOOP },
      [HID_KEY_SPACE]               = { HID_KEY_PERIOD,         KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // :
    },

    // -----------------------------------------------------------------------
    // LAYER 2: NAV (Windows AHK)
    // -----------------------------------------------------------------------
    [FAMAK_LAYER_NAV] = {
      [HID_KEY_1]                   = { HID_KEY_1,              KEYBOARD_MODIFIER_LEFTALT, 0 }, // !1
      [HID_KEY_2]                   = { HID_KEY_2,              KEYBOARD_MODIFIER_LEFTALT, 0 }, // !2
      [HID_KEY_3]                   = { HID_KEY_3,              KEYBOARD_MODIFIER_LEFTALT, 0 }, // !3
      [HID_KEY_4]                   = { HID_KEY_4,              KEYBOARD_MODIFIER_LEFTALT, 0 }, // !4
      [HID_KEY_5]                   = { HID_KEY_5,              KEYBOARD_MODIFIER_LEFTALT, 0 }, // !5
      [HID_KEY_6]                   = { HID_KEY_6,              KEYBOARD_MODIFIER_LEFTALT, 0 }, // !6
      [HID_KEY_7]                   = { HID_KEY_7,              KEYBOARD_MODIFIER_LEFTALT, 0 }, // !7
      [HID_KEY_8]                   = { HID_KEY_8,              KEYBOARD_MODIFIER_LEFTALT, 0 }, // !8
      [HID_KEY_9]                   = { HID_KEY_9,              KEYBOARD_MODIFIER_LEFTALT, 0 }, // !9
      [HID_KEY_0]                   = { HID_KEY_0,              KEYBOARD_MODIFIER_LEFTALT, 0 }, // !!0
      [HID_KEY_MINUS]               = { HID_KEY_1,              KEYBOARD_MODIFIER_LEFTALT, 0 }, // !!1
      [HID_KEY_EQUAL]               = { HID_KEY_2,              KEYBOARD_MODIFIER_LEFTALT, 0 }, // !!2
      [HID_KEY_BACKSPACE]           = { HID_KEY_F4,             KEYBOARD_MODIFIER_LEFTALT, 0 }, // !{f4}

      [HID_KEY_Q]                   = { HID_KEY_W,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!w
      [HID_KEY_W]                   = { HID_KEY_ARROW_LEFT,     0, FLAG_PASS_MODS },            // {Left}
      [HID_KEY_E]                   = { HID_KEY_ARROW_UP,       0, FLAG_PASS_MODS },            // {Up}
      [HID_KEY_R]                   = { HID_KEY_ARROW_RIGHT,    0, FLAG_PASS_MODS },            // {Right}
      [HID_KEY_T]                   = { HID_KEY_T,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!t
      [HID_KEY_Y]                   = { HID_KEY_MUTE,           0, 0 },                          // {mute}
      [HID_KEY_U]                   = { HID_KEY_F14,            0, 0 },                          // {brightnessdown}
      [HID_KEY_I]                   = { HID_KEY_F15,            0, 0 },                          // {brightnessup}
      [HID_KEY_O]                   = { HID_KEY_8,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // [
      [HID_KEY_P]                   = { HID_KEY_9,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // ]
      [HID_KEY_BRACKET_LEFT]        = { HID_KEY_ESCAPE,         0, FLAG_PASS_MODS },            // {Esc}
      [HID_KEY_BRACKET_RIGHT]       = { 0,                      KEYBOARD_MODIFIER_RIGHTSHIFT, 0 }, // {rightshift}
      [HID_KEY_CAPS_LOCK]           = { 0,                      KEYBOARD_MODIFIER_LEFTCTRL, 0 },

      [HID_KEY_A]                   = { HID_KEY_HOME,           0, FLAG_PASS_MODS },            // {Home}
      [HID_KEY_S]                   = { HID_KEY_ARROW_LEFT,     KEYBOARD_MODIFIER_LEFTCTRL, FLAG_PASS_MODS }, // ^{Left}
      [HID_KEY_D]                   = { HID_KEY_ARROW_DOWN,     0, FLAG_PASS_MODS },            // {Down}
      [HID_KEY_F]                   = { HID_KEY_ARROW_RIGHT,    KEYBOARD_MODIFIER_LEFTCTRL, FLAG_PASS_MODS }, // ^{Right}
      [HID_KEY_G]                   = { HID_KEY_END,            0, FLAG_PASS_MODS },            // {End}
      [HID_KEY_H]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_J]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_K]                   = { HID_KEY_8,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // (
      [HID_KEY_L]                   = { HID_KEY_9,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // )
      [HID_KEY_SEMICOLON]           = { HID_KEY_L,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^l
      [HID_KEY_APOSTROPHE]          = { HID_KEY_DELETE,         0, FLAG_PASS_MODS },            // {Delete}

      [HID_KEY_EUROPE_2]            = { HID_KEY_4,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // $
      [HID_KEY_Z]                   = { HID_KEY_INSERT,         0, FLAG_PASS_MODS },            // {Insert}
      [HID_KEY_X]                   = { HID_KEY_EUROPE_1,       KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // ' (Shift+#)
      [HID_KEY_C]                   = { HID_KEY_PAGE_DOWN,      KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // !{pagedown}
      [HID_KEY_V]                   = { HID_KEY_PAGE_UP,        KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // !{pageup}
      [HID_KEY_B]                   = { HID_KEY_2,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // "
      [HID_KEY_N]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_M]                   = { HID_KEY_7,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // {
      [HID_KEY_COMMA]               = { HID_KEY_0,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // }
      [HID_KEY_PERIOD]              = { 0, 0, FLAG_NOOP },
      [HID_KEY_SLASH]               = { 0, 0, FLAG_NOOP },
      [HID_KEY_SPACE]               = { HID_KEY_TAB,            0, FLAG_PASS_MODS },            // {Tab}
    },

    // -----------------------------------------------------------------------
    // LAYER 3: EXO (Windows AHK)
    // -----------------------------------------------------------------------
    [FAMAK_LAYER_EXO] = {
      [HID_KEY_1]                   = { HID_KEY_1,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // +^1
      [HID_KEY_2]                   = { HID_KEY_2,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // +^2
      [HID_KEY_3]                   = { HID_KEY_C,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // +^c
      [HID_KEY_4]                   = { HID_KEY_V,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // +^v
      [HID_KEY_5]                   = { HID_KEY_F2,             0, 0 },                          // {f2}
      [HID_KEY_6]                   = { HID_KEY_F3,             0, 0 },                          // {f3}
      [HID_KEY_7]                   = { HID_KEY_F4,             0, 0 },                          // {f4}
      [HID_KEY_8]                   = { HID_KEY_F10,            0, 0 },                          // {f10}
      [HID_KEY_9]                   = { HID_KEY_F11,            0, 0 },                          // {f11}
      [HID_KEY_0]                   = { HID_KEY_PAGE_DOWN,      0, FLAG_PASS_MODS },            // scrolldown
      [HID_KEY_MINUS]               = { HID_KEY_PAGE_UP,        0, FLAG_PASS_MODS },            // scrollup
      [HID_KEY_EQUAL]               = { HID_KEY_F10,            KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // +{f10}
      [HID_KEY_BACKSPACE]           = { HID_KEY_ESCAPE,         KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!{Esc}

      [HID_KEY_Q]                   = { HID_KEY_ARROW_LEFT,     KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // ^!{Left}
      [HID_KEY_W]                   = { HID_KEY_ARROW_RIGHT,    KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // ^!{Right}
      [HID_KEY_E]                   = { HID_KEY_ARROW_UP,       KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // ^!{Up}
      [HID_KEY_R]                   = { HID_KEY_PAGE_UP,        KEYBOARD_MODIFIER_LEFTCTRL, FLAG_PASS_MODS }, // ^{pageup}
      [HID_KEY_T]                   = { HID_KEY_PAGE_DOWN,      KEYBOARD_MODIFIER_LEFTCTRL, FLAG_PASS_MODS }, // ^{pagedown}
      [HID_KEY_Y]                   = { HID_KEY_VOLUME_UP,      0, 0 },                          // {volumeup}
      [HID_KEY_U]                   = { HID_KEY_Q,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // @
      [HID_KEY_I]                   = { HID_KEY_7,              0, FLAG_PASS_MODS },            // 7
      [HID_KEY_O]                   = { HID_KEY_8,              0, FLAG_PASS_MODS },            // 8
      [HID_KEY_P]                   = { HID_KEY_9,              0, FLAG_PASS_MODS },            // 9
      [HID_KEY_BRACKET_LEFT]        = { HID_KEY_BACKSPACE,      0, FLAG_PASS_MODS },            // {Backspace}
      [HID_KEY_BRACKET_RIGHT]       = { 0,                      KEYBOARD_MODIFIER_RIGHTSHIFT, 0 }, // {rightshift}
      [HID_KEY_CAPS_LOCK]           = { 0,                      KEYBOARD_MODIFIER_LEFTCTRL, 0 },

      [HID_KEY_A]                   = { HID_KEY_HOME,           KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // ^!{Home}
      [HID_KEY_S]                   = { HID_KEY_HOME,           KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // !{Home}
      [HID_KEY_D]                   = { HID_KEY_ARROW_DOWN,     KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // ^!{Down}
      [HID_KEY_F]                   = { HID_KEY_END,            KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // !{End}
      [HID_KEY_G]                   = { HID_KEY_END,            KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // ^!{End}
      [HID_KEY_H]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_J]                   = { HID_KEY_PERIOD,         0, FLAG_PASS_MODS },            // .
      [HID_KEY_K]                   = { HID_KEY_4,              0, FLAG_PASS_MODS },            // 4
      [HID_KEY_L]                   = { HID_KEY_5,              0, FLAG_PASS_MODS },            // 5
      [HID_KEY_SEMICOLON]           = { HID_KEY_6,              0, FLAG_PASS_MODS },            // 6
      [HID_KEY_APOSTROPHE]          = { HID_KEY_0,              0, FLAG_PASS_MODS },            // 0

      [HID_KEY_EUROPE_2]            = { HID_KEY_POWER,          0, 0 },                          // {sleep}
      [HID_KEY_Z]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_X]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_C]                   = { HID_KEY_PAGE_DOWN,      KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // ^!{pagedown}
      [HID_KEY_V]                   = { HID_KEY_PAGE_UP,        KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, FLAG_PASS_MODS }, // ^!{pageup}
      [HID_KEY_B]                   = { HID_KEY_DELETE,         0, FLAG_PASS_MODS },            // {Delete}
      [HID_KEY_N]                   = { 0, 0, FLAG_NOOP },
      [HID_KEY_M]                   = { HID_KEY_1,              0, FLAG_PASS_MODS },            // 1
      [HID_KEY_COMMA]               = { HID_KEY_2,              0, FLAG_PASS_MODS },            // 2
      [HID_KEY_PERIOD]              = { HID_KEY_3,              0, FLAG_PASS_MODS },            // 3
      [HID_KEY_SLASH]               = { HID_KEY_MINUS,          0, FLAG_PASS_MODS },            // ß (German layout produces ß for scancode -)
      [HID_KEY_SPACE]               = { HID_KEY_W,              KEYBOARD_MODIFIER_LEFTALT, 0 }, // !w
    },
  }
};
