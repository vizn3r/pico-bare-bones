#pragma once

#include <stdint.h>

void hw_gpio_enable_led();

void hw_gpio_led_blink(uint16_t n);
void hw_gpio_led_blink_fast(uint16_t n);
