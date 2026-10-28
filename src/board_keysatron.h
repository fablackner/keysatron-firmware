#ifndef BOARD_KEYSATRON_H_
#define BOARD_KEYSATRON_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

// LED is connected to GPIOA Pin 0 (active high, drives green LED D3 through 1k resistor)
#define LED_PIN       0
#define LED_PORT      GPIOA

void board_init(void);
void board_led_write(bool state);
void board_led_toggle(void);
uint32_t board_millis(void);
void board_delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif // BOARD_KEYSATRON_H_
