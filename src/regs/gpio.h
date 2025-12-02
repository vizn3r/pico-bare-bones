//
// GPIO peripheral registers
//

#pragma once

#include <stdint.h>

//
// RESETS_BASE
//

#define HW_RESETS_BASE(offset) (0x4000c000 + (offset))

#define HW_RESETS_RESET_RST 0x1
#define HW_RESETS_WDSEL_RST 0x0
#define HW_RESETS_DONE_RST 0x0

#define HW_RESETS_RESET(peripheral) *(volatile uint32_t *)HW_RESETS_BASE(0x0)

#define HW_RESETS_RESET_CLR(peripheral)                                        \
  HW_RESETS_RESET(peripheral) &= ~(HW_RESETS_RESET_RST << (peripheral))

#define HW_RESETS_WDSEL(watchdog) *(volatile uint32_t *)HW_RESETS_BASE(0x4)

#define HW_RESETS_WDSEL_CLR(watchdog)                                          \
  HW_RESETS_WDSEL(watchdog) &= ~(HW_RESETS_WDSEL_RST << (watchdog))

#define HW_RESETS_RESET_DONE(done) *(volatile uint32_t *)HW_RESETS_BASE(0x8)

#define HW_RESETS_RESET_DONE_OK(done)                                          \
  (HW_RESETS_RESET_DONE(done) & (1 << (done)))

// Reset bits
#define HW_RESETS_RESET_OFFSET_USBCTRL 24
#define HW_RESETS_RESET_OFFSET_UART1 23
#define HW_RESETS_RESET_OFFSET_UART0 22
#define HW_RESETS_RESET_OFFSET_TIMER 21
#define HW_RESETS_RESET_OFFSET_TBMAN 20
#define HW_RESETS_RESET_OFFSET_SYSINFO 19
#define HW_RESETS_RESET_OFFSET_SYSCFG 18
#define HW_RESETS_RESET_OFFSET_SPI1 17
#define HW_RESETS_RESET_OFFSET_SPI0 16
#define HW_RESETS_RESET_OFFSET_RTC 15
#define HW_RESETS_RESET_OFFSET_PWM 14
#define HW_RESETS_RESET_OFFSET_PLL_USB 13
#define HW_RESETS_RESET_OFFSET_PLL_SYS 12
#define HW_RESETS_RESET_OFFSET_PIO1 11
#define HW_RESETS_RESET_OFFSET_PIO0 10
#define HW_RESETS_RESET_OFFSET_PADS_QSPI 9
#define HW_RESETS_RESET_OFFSET_PADS_BANK0 8
#define HW_RESETS_RESET_OFFSET_JTAG 7
#define HW_RESETS_RESET_OFFSET_IO_QSPI 6
#define HW_RESETS_RESET_OFFSET_IO_BANK0 5
#define HW_RESETS_RESET_OFFSET_I2C1 4
#define HW_RESETS_RESET_OFFSET_I2C0 3
#define HW_RESETS_RESET_OFFSET_DMA 2
#define HW_RESETS_RESET_OFFSET_BUSCTRL 1
#define HW_RESETS_RESET_OFFSET_ADC 0

//
// IO_BANK0_BASE
//
//
#define HW_IO_BANK0_BASE(offset) (0x40014000 + (offset))

#define HW_GPIO_STAT(gpio) *(volatile uint32_t *)HW_IO_BANK0_BASE((gpio) * 8)
#define HW_GPIO_CTRL(gpio)                                                     \
  *(volatile uint32_t *)HW_IO_BANK0_BASE(((gpio) * 8) + 4)

#define HW_GPIO_CTRL_OEOVER 12
#define HW_OEOVER_NORMAL 0x0
#define HW_OEOVER_INVERT 0x1
#define HW_OEOVER_DISABLE 0x2
#define HW_OEOVER_ENABLE 0x3

#define HW_GPIO_CTRL_OUTOVER 8
#define HW_OUTOVER_NORMAL 0x0
#define HW_OUTOVER_INVERT 0x1
#define HW_OUTOVER_LOW 0x2
#define HW_OUTOVER_HIGH 0x3

//
// SIO_BASE
//

#define HW_SIO_BASE(offset) (0xd0000000 + (offset))

#define HW_SIO_GPIO_OUT_SET(gpio)                                              \
  *(volatile uint32_t *)HW_SIO_BASE(0x14) = (1 << (gpio))

#define HW_SIO_GPIO_OUT_CLR(gpio)                                              \
  *(volatile uint32_t *)HW_SIO_BASE(0x18) = (1 << (gpio))

#define HW_SIO_GPIO_OE_SET(gpio)                                               \
  *(volatile uint32_t *)HW_SIO_BASE(0x024) = (1 << (gpio))

#define HW_LED_GPIO 25
