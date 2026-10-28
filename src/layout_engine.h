#ifndef LAYOUT_ENGINE_H_
#define LAYOUT_ENGINE_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  LAYOUT_MODE_COLEMAK_DE = 0, // German Host OS (Colemak mapped for QWERTZ host)
  LAYOUT_MODE_COLEMAK_US = 1, // US Host OS (Standard Colemak)
  LAYOUT_MODE_PASSTHROUGH = 2, // No translation (Raw German ISO)
  LAYOUT_MODE_COUNT
} layout_mode_t;

void layout_engine_init(void);
layout_mode_t layout_get_mode(void);
void layout_set_mode(layout_mode_t mode);
layout_mode_t layout_cycle_mode(void);

// Remap a single HID keycode according to the active mode
uint8_t layout_remap_key(uint8_t keycode, layout_mode_t mode);

// Process an entire 6KRO report, check for hotkeys, and return translated report
// Returns true if mode was changed
bool layout_process_report(const uint8_t in_modifier, const uint8_t in_keys[6],
                           uint8_t* out_modifier, uint8_t out_keys[6]);

#ifdef __cplusplus
}
#endif

#endif // LAYOUT_ENGINE_H_
