#ifndef LAYOUT_ENGINE_H_
#define LAYOUT_ENGINE_H_

#include <stdint.h>
#include <stdbool.h>
#include "famak_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  LAYOUT_EVENT_NONE = 0,
  LAYOUT_EVENT_ACTIVATION_CHANGED,
  LAYOUT_EVENT_PROFILE_CHANGED
} layout_event_t;

void layout_engine_init(void);
bool layout_is_active(void);
void layout_set_active(bool active);
famak_layer_t layout_get_active_layer(void);

famak_profile_t layout_get_profile(void);
void layout_set_profile(famak_profile_t profile);
famak_profile_t layout_cycle_profile(void);

// Process an incoming 6KRO report, evaluate layer keys, apply famak mapping,
// and populate the outgoing report. Returns event if activation or profile changed.
layout_event_t layout_process_report(const uint8_t in_modifier, const uint8_t in_keys[6],
                                     uint8_t* out_modifier, uint8_t out_keys[6]);

#ifdef __cplusplus
}
#endif

#endif // LAYOUT_ENGINE_H_
