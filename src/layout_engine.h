#ifndef LAYOUT_ENGINE_H_
#define LAYOUT_ENGINE_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  FAMAK_LAYER_NORMAL = 0,
  FAMAK_LAYER_SYM    = 1,
  FAMAK_LAYER_NAV    = 2,
  FAMAK_LAYER_EXO    = 3,
  FAMAK_LAYER_COUNT
} famak_layer_t;

void layout_engine_init(void);
bool layout_is_active(void);
void layout_set_active(bool active);
famak_layer_t layout_get_active_layer(void);

// Process an incoming 6KRO report, evaluate layer keys, apply famak mapping,
// and populate the outgoing report. Returns true if keymap activation state changed.
bool layout_process_report(const uint8_t in_modifier, const uint8_t in_keys[6],
                           uint8_t* out_modifier, uint8_t out_keys[6]);

#ifdef __cplusplus
}
#endif

#endif // LAYOUT_ENGINE_H_
