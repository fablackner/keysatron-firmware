#include "board_keysatron.h"
#include "tusb.h"

static volatile uint32_t system_ticks = 0;

void SysTick_Handler(void) {
  system_ticks++;
}

uint32_t board_millis(void) {
  return system_ticks;
}

uint32_t tusb_time_millis_api(void) {
  return system_ticks;
}

void board_delay_ms(uint32_t ms) {
  uint32_t start = system_ticks;
  while ((system_ticks - start) < ms) {
    __NOP();
  }
}

void tusb_time_delay_ms_api(uint32_t ms) {
  board_delay_ms(ms);
}

void board_led_write(bool state) {
  if (state) {
    LED_PORT->BSRR = (1U << LED_PIN);
  } else {
    LED_PORT->BSRR = (1U << (LED_PIN + 16));
  }
}

void board_led_toggle(void) {
  LED_PORT->ODR ^= (1U << LED_PIN);
}

// System Clock Configuration:
// HSE = 16 MHz Crystal (PH0/PH1)
// SYSCLK = 168 MHz
// USB Clock = 48 MHz
static void clock_init(void) {
  // Enable Power Controller clock
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  PWR->CR |= PWR_CR_VOS; // High-performance mode (Scale 1)

  // Configure Flash latency: 5 wait states for 168 MHz at 3.3V
  FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;

  // Turn on HSE
  RCC->CR |= RCC_CR_HSEON;
  while (!(RCC->CR & RCC_CR_HSERDY)) {}

  // PLL Configuration:
  // Input: HSE = 16 MHz
  // PLLM = 8  -> 2 MHz VCO input (must be 1-2 MHz)
  // PLLN = 168 -> 336 MHz VCO output
  // PLLP = 2 (0b00) -> 168 MHz SYSCLK
  // PLLQ = 7 -> 48 MHz USB OTG Clock
  RCC->PLLCFGR = (8U << RCC_PLLCFGR_PLLM_Pos) |
                 (168U << RCC_PLLCFGR_PLLN_Pos) |
                 (0U << RCC_PLLCFGR_PLLP_Pos) |   // Div 2
                 (RCC_PLLCFGR_PLLSRC_HSE) |
                 (7U << RCC_PLLCFGR_PLLQ_Pos);

  // Turn on PLL
  RCC->CR |= RCC_CR_PLLON;
  while (!(RCC->CR & RCC_CR_PLLRDY)) {}

  // Bus dividers:
  // AHB Prescaler = 1 -> HCLK = 168 MHz
  // APB1 Prescaler = 4 -> PCLK1 = 42 MHz (max 42 MHz)
  // APB2 Prescaler = 2 -> PCLK2 = 84 MHz (max 84 MHz)
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2;

  // Switch SYSCLK to PLL
  RCC->CFGR &= ~RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {}

  SystemCoreClock = 168000000;
}

void board_init(void) {
  clock_init();

  // 1ms SysTick
  SysTick_Config(SystemCoreClock / 1000);

  // Enable GPIO clocks
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOHEN;

  // Configure LED Pin (PA0: Output, Push-Pull, High Speed, No Pull)
  GPIOA->MODER   &= ~(3U << (LED_PIN * 2));
  GPIOA->MODER   |= (1U << (LED_PIN * 2)); // Output mode
  GPIOA->OTYPER  &= ~(1U << LED_PIN);      // Push-Pull
  GPIOA->OSPEEDR |= (3U << (LED_PIN * 2)); // Very High Speed
  GPIOA->PUPDR   &= ~(3U << (LED_PIN * 2)); // No Pull
  board_led_write(false);

  // Configure USB OTG FS Pins (PA11: DM, PA12: DP) -> Alternate Function AF10
  GPIOA->MODER   &= ~((3U << (11 * 2)) | (3U << (12 * 2)));
  GPIOA->MODER   |= ((2U << (11 * 2)) | (2U << (12 * 2))); // Alternate Function
  GPIOA->AFR[1]  &= ~((15U << ((11 - 8) * 4)) | (15U << ((12 - 8) * 4)));
  GPIOA->AFR[1]  |= ((10U << ((11 - 8) * 4)) | (10U << ((12 - 8) * 4))); // AF10
  GPIOA->OSPEEDR |= ((3U << (11 * 2)) | (3U << (12 * 2))); // Very High Speed
  GPIOA->PUPDR   &= ~((3U << (11 * 2)) | (3U << (12 * 2)));

  // Configure USB OTG HS Pins in FS PHY Mode (PB14: DM, PB15: DP) -> Alternate Function AF12
  GPIOB->MODER   &= ~((3U << (14 * 2)) | (3U << (15 * 2)));
  GPIOB->MODER   |= ((2U << (14 * 2)) | (2U << (15 * 2))); // Alternate Function
  GPIOB->AFR[1]  &= ~((15U << ((14 - 8) * 4)) | (15U << ((15 - 8) * 4)));
  GPIOB->AFR[1]  |= ((12U << ((14 - 8) * 4)) | (12U << ((15 - 8) * 4))); // AF12
  GPIOB->OSPEEDR |= ((3U << (14 * 2)) | (3U << (15 * 2))); // Very High Speed
  GPIOB->PUPDR   &= ~((3U << (14 * 2)) | (3U << (15 * 2)));

  // Enable USB OTG Peripherals Clock
  RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_OTGHSEN;

  // Configure and Enable USB Interrupts in NVIC
  NVIC_SetPriority(OTG_FS_IRQn, 5);
  NVIC_EnableIRQ(OTG_FS_IRQn);

  NVIC_SetPriority(OTG_HS_IRQn, 5);
  NVIC_EnableIRQ(OTG_HS_IRQn);
}

// Forward USB Interrupts to TinyUSB
void OTG_FS_IRQHandler(void) {
  tusb_int_handler(0, true);
}

void OTG_HS_IRQHandler(void) {
  tusb_int_handler(1, true);
}
