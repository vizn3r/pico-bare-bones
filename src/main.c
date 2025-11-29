#include "../lib/gpio.h"

int main(void) {
  RESETS_RESET_CLR(RESET_IO_BANK0);
  RESETS_RESET_CLR(RESET_PADS_BANK0);

  while (!(RESETS_RESET_DONE_OK(RESET_IO_BANK0)))
    ;
  while (!(RESETS_RESET_DONE_OK(RESET_PADS_BANK0)))
    ;

  GPIO_CTRL(LED_GPIO) = 5;

  SIO_GPIO_OE_SET(LED_GPIO);
  SIO_GPIO_OUT_SET(LED_GPIO);

  while (1) {
    SIO_GPIO_OUT_SET(LED_GPIO);
    for (volatile int i = 0; i < 10000; i++)
      ;
    SIO_GPIO_OUT_CLR(LED_GPIO);
    for (volatile int i = 0; i < 10000; i++)
      ;
  }
  return 0;
}
