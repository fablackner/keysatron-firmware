#include "layout_engine.h"
#include "tusb.h"

typedef struct {
  uint8_t keycode;
  uint8_t modifiers;
  uint8_t flags;
} map_entry_t;

#define FLAG_NONE       0x00
#define FLAG_PASS_MODS  0x01 // Merge with user Shift / Ctrl / Alt / GUI
#define FLAG_NOOP       0x02 // Inactive in this layer

static bool keymap_is_active = true;
static famak_layer_t current_layer = FAMAK_LAYER_NORMAL;

// Tables: [layer][input_keycode] -> map_entry_t
static const map_entry_t layer_tables[FAMAK_LAYER_COUNT][256] = {
  //--------------------------------------------------------------------------
  // LAYER 0: NORMAL (FAMAK Layout)
  //--------------------------------------------------------------------------
  [FAMAK_LAYER_NORMAL] = {
    // Row 1 (Number row)
    [HID_KEY_1]                   = { HID_KEY_ARROW_LEFT,     KEYBOARD_MODIFIER_LEFTALT, 0 }, // !{Left}
    [HID_KEY_2]                   = { HID_KEY_ARROW_RIGHT,    KEYBOARD_MODIFIER_LEFTALT, 0 }, // !{Right}
    [HID_KEY_3]                   = { HID_KEY_Z,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^y (German OS produces 'y' for HID_KEY_Z)
    [HID_KEY_4]                   = { HID_KEY_Y,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^z (German OS produces 'z' for HID_KEY_Y)
    [HID_KEY_5]                   = { HID_KEY_F5,             0, 0 },                         // {f5}
    [HID_KEY_6]                   = { HID_KEY_F6,             0, 0 },                         // {f6}
    [HID_KEY_7]                   = { HID_KEY_F7,             0, 0 },                         // {f7}
    [HID_KEY_8]                   = { HID_KEY_F8,             0, 0 },                         // {f8}
    [HID_KEY_9]                   = { HID_KEY_F9,             0, 0 },                         // {f9}
    [HID_KEY_0]                   = { HID_KEY_PAGE_DOWN,      0, 0 },                         // {pagedown}
    [HID_KEY_MINUS]               = { HID_KEY_PAGE_UP,        0, 0 },                         // {pageup}
    [HID_KEY_EQUAL]               = { HID_KEY_B,              KEYBOARD_MODIFIER_LEFTALT | KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // !+b

    // Row 2
    [HID_KEY_Q]                   = { HID_KEY_Q,              0, FLAG_PASS_MODS },            // q
    [HID_KEY_W]                   = { HID_KEY_W,              0, FLAG_PASS_MODS },            // w
    [HID_KEY_E]                   = { HID_KEY_C,              0, FLAG_PASS_MODS },            // c
    [HID_KEY_R]                   = { HID_KEY_P,              0, FLAG_PASS_MODS },            // p
    [HID_KEY_T]                   = { HID_KEY_B,              0, FLAG_PASS_MODS },            // b
    [HID_KEY_Y]                   = { HID_KEY_VOLUME_DOWN,    0, 0 },                         // {volumedown} (physical Z)
    [HID_KEY_U]                   = { HID_KEY_J,              0, FLAG_PASS_MODS },            // j
    [HID_KEY_I]                   = { HID_KEY_L,              0, FLAG_PASS_MODS },            // l
    [HID_KEY_O]                   = { HID_KEY_U,              0, FLAG_PASS_MODS },            // u
    [HID_KEY_P]                   = { HID_KEY_Y,              0, FLAG_PASS_MODS },            // z (German OS produces 'z' for HID_KEY_Y)
    [HID_KEY_BRACKET_LEFT]        = { HID_KEY_BACKSPACE,      0, 0 },                         // {Backspace} (physical Ü)

    // Row 3
    [HID_KEY_A]                   = { HID_KEY_A,              0, FLAG_PASS_MODS },            // a
    [HID_KEY_S]                   = { HID_KEY_R,              0, FLAG_PASS_MODS },            // r
    [HID_KEY_D]                   = { HID_KEY_S,              0, FLAG_PASS_MODS },            // s
    [HID_KEY_F]                   = { HID_KEY_T,              0, FLAG_PASS_MODS },            // t
    [HID_KEY_G]                   = { HID_KEY_G,              0, FLAG_PASS_MODS },            // g
    [HID_KEY_H]                   = { HID_KEY_H,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!h
    [HID_KEY_J]                   = { HID_KEY_M,              0, FLAG_PASS_MODS },            // m
    [HID_KEY_K]                   = { HID_KEY_N,              0, FLAG_PASS_MODS },            // n
    [HID_KEY_L]                   = { HID_KEY_E,              0, FLAG_PASS_MODS },            // e
    [HID_KEY_SEMICOLON]           = { HID_KEY_I,              0, FLAG_PASS_MODS },            // i (physical Ö)
    [HID_KEY_APOSTROPHE]          = { HID_KEY_O,              0, FLAG_PASS_MODS },            // o (physical Ä)

    // Row 4
    [HID_KEY_EUROPE_2]            = { HID_KEY_Z,              0, FLAG_PASS_MODS },            // y (German OS produces 'y' for HID_KEY_Z) (physical <)
    [HID_KEY_Z]                   = { HID_KEY_COMMA,          KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // ; (Shift+, on German) (physical Y)
    [HID_KEY_X]                   = { HID_KEY_F,              0, FLAG_PASS_MODS },            // f
    [HID_KEY_C]                   = { HID_KEY_D,              0, FLAG_PASS_MODS },            // d
    [HID_KEY_V]                   = { HID_KEY_V,              0, FLAG_PASS_MODS },            // v
    [HID_KEY_B]                   = { HID_KEY_X,              0, FLAG_PASS_MODS },            // x
    [HID_KEY_N]                   = { 0,                      KEYBOARD_MODIFIER_LEFTGUI, 0 }, // {leftmeta}
    [HID_KEY_M]                   = { HID_KEY_K,              0, FLAG_PASS_MODS },            // k
    [HID_KEY_COMMA]               = { HID_KEY_H,              0, FLAG_PASS_MODS },            // h
    [HID_KEY_PERIOD]              = { HID_KEY_8,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // [ (AltGr+8 on German)
    [HID_KEY_SLASH]               = { HID_KEY_EUROPE_1,       KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // ' (Shift+# on German) (physical -)

    // CapsLock -> Left Control
    [HID_KEY_CAPS_LOCK]           = { 0,                      KEYBOARD_MODIFIER_LEFTCTRL, 0 },
    [HID_KEY_SPACE]               = { HID_KEY_SPACE,          0, FLAG_PASS_MODS },
  },

  //--------------------------------------------------------------------------
  // LAYER 1: SYM (when # held, or in Exo when # held)
  //--------------------------------------------------------------------------
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

    [HID_KEY_Q]                   = { HID_KEY_BRACKET_RIGHT,  KEYBOARD_MODIFIER_RIGHTALT, 0 }, // ~ (AltGr++ on German)
    [HID_KEY_W]                   = { HID_KEY_1,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // ! (Shift+1)
    [HID_KEY_E]                   = { HID_KEY_7,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // / (Shift+7)
    [HID_KEY_R]                   = { HID_KEY_EUROPE_2,       KEYBOARD_MODIFIER_RIGHTALT, 0 }, // | (AltGr+<)
    [HID_KEY_T]                   = { HID_KEY_6,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // & (Shift+6)
    [HID_KEY_Y]                   = { 0, 0, FLAG_NOOP },
    [HID_KEY_U]                   = { 0, 0, FLAG_NOOP },
    [HID_KEY_I]                   = { 0, 0, FLAG_NOOP },
    [HID_KEY_O]                   = { 0, 0, FLAG_NOOP },
    [HID_KEY_P]                   = { 0, 0, FLAG_NOOP },
    [HID_KEY_BRACKET_LEFT]        = { 0, 0, FLAG_NOOP },
    [HID_KEY_BRACKET_RIGHT]       = { 0,                      KEYBOARD_MODIFIER_RIGHTSHIFT, 0 }, // {rightshift}
    [HID_KEY_CAPS_LOCK]           = { 0,                      KEYBOARD_MODIFIER_LEFTCTRL, 0 },

    [HID_KEY_A]                   = { HID_KEY_7,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // / (Shift+7)
    [HID_KEY_S]                   = { HID_KEY_9,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // ] (AltGr+9)
    [HID_KEY_D]                   = { HID_KEY_BRACKET_RIGHT,  KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // * (Shift++)
    [HID_KEY_F]                   = { HID_KEY_PERIOD,         0, 0 },                          // .
    [HID_KEY_G]                   = { HID_KEY_COMMA,          0, 0 },                          // ,
    [HID_KEY_H]                   = { HID_KEY_MINUS,          KEYBOARD_MODIFIER_RIGHTALT, 0 }, // \ (AltGr+ß)
    [HID_KEY_J]                   = { HID_KEY_0,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // = (Shift+0)
    [HID_KEY_K]                   = { HID_KEY_MINUS,          KEYBOARD_MODIFIER_RIGHTALT, 0 }, // \ (AltGr+ß)
    [HID_KEY_L]                   = { HID_KEY_EQUAL,          KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // ` (Backtick)
    [HID_KEY_SEMICOLON]           = { HID_KEY_0,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // =
    [HID_KEY_APOSTROPHE]          = { HID_KEY_EQUAL,          KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // `

    [HID_KEY_EUROPE_2]            = { HID_KEY_EUROPE_2,       0, 0 },                          // <
    [HID_KEY_Z]                   = { HID_KEY_MINUS,          KEYBOARD_MODIFIER_RIGHTALT, 0 }, // \ (AltGr+ß)
    [HID_KEY_X]                   = { HID_KEY_EUROPE_2,       KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // > (Shift+<)
    [HID_KEY_C]                   = { HID_KEY_0,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // = (Shift+0)
    [HID_KEY_V]                   = { HID_KEY_COMMA,          KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // ; (Shift+,)
    [HID_KEY_B]                   = { HID_KEY_SLASH,          KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // _ (Shift+-)
    [HID_KEY_N]                   = { 0, 0, FLAG_NOOP },
    [HID_KEY_M]                   = { 0, 0, FLAG_NOOP },
    [HID_KEY_COMMA]               = { HID_KEY_5,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // % (Shift+5)
    [HID_KEY_PERIOD]              = { 0, 0, FLAG_NOOP },
    [HID_KEY_SLASH]               = { 0, 0, FLAG_NOOP },
    [HID_KEY_SPACE]               = { HID_KEY_EUROPE_2,       KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // > (Shift+<)
  },

  //--------------------------------------------------------------------------
  // LAYER 2: NAV (when AltGr held)
  //--------------------------------------------------------------------------
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
    [HID_KEY_0]                   = { HID_KEY_0,              KEYBOARD_MODIFIER_LEFTALT, 0 }, // !0
    [HID_KEY_MINUS]               = { HID_KEY_MINUS,          KEYBOARD_MODIFIER_LEFTALT, 0 }, // !ß
    [HID_KEY_EQUAL]               = { HID_KEY_EQUAL,          KEYBOARD_MODIFIER_LEFTALT, 0 }, // !´
    [HID_KEY_BACKSPACE]           = { HID_KEY_F4,             KEYBOARD_MODIFIER_LEFTALT, 0 }, // !{f4}

    [HID_KEY_Q]                   = { HID_KEY_W,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!w
    [HID_KEY_W]                   = { HID_KEY_ARROW_LEFT,     0, 0 },                          // {Left}
    [HID_KEY_E]                   = { HID_KEY_ARROW_UP,       0, 0 },                          // {Up}
    [HID_KEY_R]                   = { HID_KEY_ARROW_RIGHT,    0, 0 },                          // {Right}
    [HID_KEY_T]                   = { HID_KEY_T,              KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!t
    [HID_KEY_Y]                   = { HID_KEY_MUTE,           0, 0 },                          // {mute}
    [HID_KEY_U]                   = { HID_KEY_F14,            0, 0 },                          // {brightnessdown}
    [HID_KEY_I]                   = { HID_KEY_F15,            0, 0 },                          // {brightnessup}
    [HID_KEY_O]                   = { HID_KEY_8,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // [ (AltGr+8)
    [HID_KEY_P]                   = { HID_KEY_9,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // ] (AltGr+9)
    [HID_KEY_BRACKET_LEFT]        = { HID_KEY_ESCAPE,         0, 0 },                          // {Esc}
    [HID_KEY_BRACKET_RIGHT]       = { 0,                      KEYBOARD_MODIFIER_RIGHTSHIFT, 0 }, // {rightshift}
    [HID_KEY_CAPS_LOCK]           = { 0,                      KEYBOARD_MODIFIER_LEFTCTRL, 0 },

    [HID_KEY_A]                   = { HID_KEY_HOME,           0, 0 },                          // {Home}
    [HID_KEY_S]                   = { HID_KEY_ARROW_LEFT,     KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^{Left}
    [HID_KEY_D]                   = { HID_KEY_ARROW_DOWN,     0, 0 },                          // {Down}
    [HID_KEY_F]                   = { HID_KEY_ARROW_RIGHT,    KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^{Right}
    [HID_KEY_G]                   = { HID_KEY_END,            0, 0 },                          // {End}
    [HID_KEY_H]                   = { 0, 0, FLAG_NOOP },
    [HID_KEY_J]                   = { 0, 0, FLAG_NOOP },
    [HID_KEY_K]                   = { HID_KEY_8,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // ( (Shift+8)
    [HID_KEY_L]                   = { HID_KEY_9,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // ) (Shift+9)
    [HID_KEY_SEMICOLON]           = { HID_KEY_L,              KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^l
    [HID_KEY_APOSTROPHE]          = { HID_KEY_DELETE,         0, 0 },                          // {Delete}

    [HID_KEY_EUROPE_2]            = { HID_KEY_4,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // $ (Shift+4)
    [HID_KEY_Z]                   = { HID_KEY_INSERT,         0, 0 },                          // {Insert}
    [HID_KEY_X]                   = { HID_KEY_MINUS,          KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // ? (Shift+ß)
    [HID_KEY_C]                   = { HID_KEY_PAGE_DOWN,      KEYBOARD_MODIFIER_LEFTALT, 0 }, // !{pagedown}
    [HID_KEY_V]                   = { HID_KEY_PAGE_UP,        KEYBOARD_MODIFIER_LEFTALT, 0 }, // !{pageup}
    [HID_KEY_B]                   = { HID_KEY_2,              KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // " (Shift+2)
    [HID_KEY_N]                   = { 0, 0, FLAG_NOOP },
    [HID_KEY_M]                   = { HID_KEY_7,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // { (AltGr+7)
    [HID_KEY_COMMA]               = { HID_KEY_0,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // } (AltGr+0)
    [HID_KEY_PERIOD]              = { 0, 0, FLAG_NOOP },
    [HID_KEY_SLASH]               = { 0, 0, FLAG_NOOP },
    [HID_KEY_SPACE]               = { HID_KEY_TAB,            0, 0 },                          // {Tab}
  },

  //--------------------------------------------------------------------------
  // LAYER 3: EXO (when Tab held, or Nav+#, or Sym+AltGr)
  //--------------------------------------------------------------------------
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
    [HID_KEY_0]                   = { HID_KEY_PAGE_DOWN,      0, 0 },                          // scrolldown / {pagedown}
    [HID_KEY_MINUS]               = { HID_KEY_PAGE_UP,        0, 0 },                          // scrollup / {pageup}
    [HID_KEY_EQUAL]               = { HID_KEY_F10,            KEYBOARD_MODIFIER_LEFTSHIFT, 0 }, // +{f10}
    [HID_KEY_BACKSPACE]           = { HID_KEY_ESCAPE,         KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!{Esc}

    [HID_KEY_Q]                   = { HID_KEY_ARROW_LEFT,     KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!{Left}
    [HID_KEY_W]                   = { HID_KEY_ARROW_RIGHT,    KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!{Right}
    [HID_KEY_E]                   = { HID_KEY_ARROW_UP,       KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!{Up}
    [HID_KEY_R]                   = { HID_KEY_PAGE_UP,        KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^{pageup}
    [HID_KEY_T]                   = { HID_KEY_PAGE_DOWN,      KEYBOARD_MODIFIER_LEFTCTRL, 0 }, // ^{pagedown}
    [HID_KEY_Y]                   = { HID_KEY_VOLUME_UP,      0, 0 },                          // {volumeup}
    [HID_KEY_U]                   = { HID_KEY_Q,              KEYBOARD_MODIFIER_RIGHTALT, 0 }, // @ (AltGr+q)
    [HID_KEY_I]                   = { HID_KEY_7,              0, 0 },                          // 7
    [HID_KEY_O]                   = { HID_KEY_8,              0, 0 },                          // 8
    [HID_KEY_P]                   = { HID_KEY_9,              0, 0 },                          // 9
    [HID_KEY_BRACKET_LEFT]        = { HID_KEY_BACKSPACE,      0, 0 },                          // {Backspace}
    [HID_KEY_BRACKET_RIGHT]       = { 0,                      KEYBOARD_MODIFIER_RIGHTSHIFT, 0 }, // {rightshift}
    [HID_KEY_CAPS_LOCK]           = { 0,                      KEYBOARD_MODIFIER_LEFTCTRL, 0 },

    [HID_KEY_A]                   = { HID_KEY_HOME,           KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!{Home}
    [HID_KEY_S]                   = { HID_KEY_HOME,           KEYBOARD_MODIFIER_LEFTALT, 0 }, // !{Home}
    [HID_KEY_D]                   = { HID_KEY_ARROW_DOWN,     KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!{Down}
    [HID_KEY_F]                   = { HID_KEY_END,            KEYBOARD_MODIFIER_LEFTALT, 0 }, // !{End}
    [HID_KEY_G]                   = { HID_KEY_END,            KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!{End}
    [HID_KEY_H]                   = { 0, 0, FLAG_NOOP },
    [HID_KEY_J]                   = { HID_KEY_PERIOD,         0, 0 },                          // .
    [HID_KEY_K]                   = { HID_KEY_4,              0, 0 },                          // 4
    [HID_KEY_L]                   = { HID_KEY_5,              0, 0 },                          // 5
    [HID_KEY_SEMICOLON]           = { HID_KEY_6,              0, 0 },                          // 6
    [HID_KEY_APOSTROPHE]          = { HID_KEY_0,              0, 0 },                          // 0

    [HID_KEY_EUROPE_2]            = { HID_KEY_POWER,          0, 0 },                          // {sleep}
    [HID_KEY_Z]                   = { 0, 0, FLAG_NOOP },
    [HID_KEY_X]                   = { 0, 0, FLAG_NOOP },
    [HID_KEY_C]                   = { HID_KEY_PAGE_DOWN,      KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!{pagedown}
    [HID_KEY_V]                   = { HID_KEY_PAGE_UP,        KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, 0 }, // ^!{pageup}
    [HID_KEY_B]                   = { HID_KEY_DELETE,         0, 0 },                          // {Delete}
    [HID_KEY_N]                   = { 0, 0, FLAG_NOOP },
    [HID_KEY_M]                   = { HID_KEY_1,              0, 0 },                          // 1
    [HID_KEY_COMMA]               = { HID_KEY_2,              0, 0 },                          // 2
    [HID_KEY_PERIOD]              = { HID_KEY_3,              0, 0 },                          // 3
    [HID_KEY_SLASH]               = { HID_KEY_SLASH,          0, 0 },                          // -
    [HID_KEY_SPACE]               = { HID_KEY_W,              KEYBOARD_MODIFIER_LEFTALT, 0 }, // !w
  }
};

void layout_engine_init(void) {
  keymap_is_active = true;
  current_layer = FAMAK_LAYER_NORMAL;
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

bool layout_process_report(const uint8_t in_modifier, const uint8_t in_keys[6],
                           uint8_t* out_modifier, uint8_t out_keys[6]) {
  bool state_changed = false;

  // Check for Win + Escape (disable) and Win + Backspace (enable)
  bool win_held = (in_modifier & (KEYBOARD_MODIFIER_LEFTGUI | KEYBOARD_MODIFIER_RIGHTGUI)) != 0;
  if (win_held) {
    for (int i = 0; i < 6; i++) {
      if (in_keys[i] == HID_KEY_ESCAPE) { // #SC001
        if (keymap_is_active) {
          keymap_is_active = false;
          state_changed = true;
        }
      } else if (in_keys[i] == HID_KEY_BACKSPACE) { // #SC00E
        if (!keymap_is_active) {
          keymap_is_active = true;
          state_changed = true;
        }
      }
    }
  }

  // If keymap is stopped, pass through raw German keys
  if (!keymap_is_active) {
    *out_modifier = in_modifier;
    for (int i = 0; i < 6; i++) {
      out_keys[i] = in_keys[i];
    }
    return state_changed;
  }

  // 1. Scan for layer hold keys
  bool exo_pressed = false;   // SC00F (Tab)
  bool sym_pressed = false;   // SC02B (#)
  bool nav_pressed = false;   // SC138 (AltGr / RAlt)
  bool shift_pressed = false; // SC01B (+)
  bool capslock_pressed = false; // SC03A (CapsLock -> LeftControl)

  for (int i = 0; i < 6; i++) {
    uint8_t k = in_keys[i];
    if (k == HID_KEY_TAB)               exo_pressed = true;
    if (k == HID_KEY_EUROPE_1)          sym_pressed = true;
    if (k == HID_KEY_BRACKET_RIGHT)     shift_pressed = true;
    if (k == HID_KEY_CAPS_LOCK)         capslock_pressed = true;
  }
  if (in_modifier & KEYBOARD_MODIFIER_RIGHTALT) {
    nav_pressed = true;
  }

  // 2. Resolve active layer based on cross-layer rules:
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

  // Determine user shift state
  bool user_shifted = ((in_modifier & (KEYBOARD_MODIFIER_LEFTSHIFT | KEYBOARD_MODIFIER_RIGHTSHIFT)) != 0) || shift_pressed;

  // Initialize output modifiers (strip RightAlt if it's consumed as Nav layer key)
  uint8_t active_mods = in_modifier;
  if (nav_pressed) {
    active_mods &= ~KEYBOARD_MODIFIER_RIGHTALT;
  }
  if (capslock_pressed) {
    active_mods |= KEYBOARD_MODIFIER_LEFTCTRL;
  }

  // 3. Process each non-layer key
  uint8_t out_idx = 0;
  uint8_t combined_forced_mods = 0;
  bool has_forced_mods = false;

  for (int i = 0; i < 6; i++) {
    uint8_t in_k = in_keys[i];
    if (in_k == 0) continue;

    // Skip layer-switch keys so they don't emit characters themselves
    if (in_k == HID_KEY_TAB && exo_pressed) continue;
    if (in_k == HID_KEY_EUROPE_1 && sym_pressed) continue;
    if (in_k == HID_KEY_BRACKET_RIGHT && shift_pressed) continue;
    if (in_k == HID_KEY_CAPS_LOCK) continue;

    // Special Space key behavior in Normal layer when Shift is active
    if (current_layer == FAMAK_LAYER_NORMAL && in_k == HID_KEY_SPACE && user_shifted) {
      // SC039 (Space) with Shift -> Send, ? (Shift + ß on German layout)
      if (out_idx < 6) {
        out_keys[out_idx++] = HID_KEY_MINUS;
        combined_forced_mods |= KEYBOARD_MODIFIER_LEFTSHIFT;
        has_forced_mods = true;
      }
      continue;
    }

    // Look up in current layer table
    map_entry_t entry = layer_tables[current_layer][in_k];

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
        // Normal letter/key: pass user modifiers (including Shift)
        if (user_shifted) {
          active_mods |= KEYBOARD_MODIFIER_LEFTSHIFT;
        }
      } else {
        // Forced modifier key (e.g. !{Left}, ^1, [ which requires AltGr, etc.)
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
      if (user_shifted) {
        active_mods |= KEYBOARD_MODIFIER_LEFTSHIFT;
      }
    }
  }

  // Clear remaining output key slots
  while (out_idx < 6) {
    out_keys[out_idx++] = 0;
  }

  // Combine modifiers:
  if (has_forced_mods) {
    // For forced shortcuts / symbols, use forced modifiers merged with user Ctrl/Alt/GUI as appropriate
    *out_modifier = combined_forced_mods | (active_mods & (KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT | KEYBOARD_MODIFIER_LEFTGUI | KEYBOARD_MODIFIER_RIGHTGUI));
  } else {
    *out_modifier = active_mods;
  }

  return state_changed;
}
