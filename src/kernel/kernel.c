#include "kernel.h"
#include "../hal/gpio.h"
#include "../serial/usb.h"
#include <stdint.h>

static int strlen(const char *s) {
  int len = 0;
  while (s[len])
    len++;
  return len;
}

int kernel_main(void) {
  hw_gpio_enable_led();

  hw_gpio_led_blink_fast(3);

  s_usb_init_blocking();
  const char *data = "Hello world!";
  while (1) {
    for (volatile int i = 0; i < 1e6; i++)
      ;
    s_usb_cdc_send((const uint8_t *)data, strlen(data));
  }

  return 0;
}
