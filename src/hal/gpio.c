#include "../regs/gpio.h"
#include <stdint.h>

void hw_gpio_enable_led() {
  HW_RESETS_RESET_CLR(HW_RESETS_RESET_OFFSET_IO_BANK0);
  HW_RESETS_RESET_CLR(HW_RESETS_RESET_OFFSET_PADS_BANK0);

  while (!HW_RESETS_RESET_DONE_OK(HW_RESETS_RESET_OFFSET_IO_BANK0))
    ;
  while (!HW_RESETS_RESET_DONE_OK(HW_RESETS_RESET_OFFSET_PADS_BANK0))
    ;

  HW_GPIO_CTRL(HW_LED_GPIO) = 5;
  HW_SIO_GPIO_OE_SET(HW_LED_GPIO);
}

void hw_gpio_led_blink(uint16_t n) {
  for (uint16_t i = 0; i < n; i++) {
    HW_SIO_GPIO_OUT_SET(HW_LED_GPIO);
    for (uint16_t i = 0; i < 1e5; i++)
      ;

    HW_SIO_GPIO_OUT_CLR(HW_LED_GPIO);
  }
}

void hw_gpio_led_blink_fast(uint16_t n) {
  for (uint16_t i = 0; i < n; i++) {
    HW_SIO_GPIO_OUT_SET(HW_LED_GPIO);
    for (uint16_t i = 0; i < 1e4; i++)
      ;

    HW_SIO_GPIO_OUT_CLR(HW_LED_GPIO);
  }
}
