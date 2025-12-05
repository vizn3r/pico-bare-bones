//
// CLOCK_BASE
//

#pragma once

#include <stdint.h>

#define CLOCK_BASE 0x40008000

typedef union {
  struct {
    uint32_t : 5;
    uint32_t auxsrc : 4;
    uint32_t : 1;
    uint32_t kill : 1;
    uint32_t enable : 1;
    uint32_t dc50 : 1;
    uint32_t : 3;
    uint32_t phase : 2;
    uint32_t : 2;
    uint32_t nudge : 1;
    uint32_t : 11;
  };
  uint32_t raw;
} clock_clk_gpout_ctrl_t;

typedef union {
  struct {
    uint32_t frac : 8;
    uint32_t integer : 24;
  };
  uint32_t raw;
} clock_clk_gpout_div_t;

typedef union {
  struct {
    uint32_t slice : 32;
  };
  uint32_t raw;
} clock_clk_gpout_selected_t;

typedef union {
  struct {
    uint32_t src : 2;
    uint32_t : 3;
    uint32_t auxsrc : 2;
    uint32_t : 25;
  };
  uint32_t raw;
} clock_clk_ref_ctrl_t;

typedef union {
  struct {
    uint32_t : 8;
    uint32_t integer : 2;
    uint32_t : 22;
  };
  uint32_t raw;
} clock_clk_ref_div_t;

typedef union {
  struct {
    uint32_t slice : 32;
  };
  uint32_t raw;
} clock_clk_ref_selected_t;

typedef union {
  struct {
    uint32_t src : 1;
    uint32_t : 4;
    uint32_t auxsrc : 3;
    uint32_t : 24;
  };
  uint32_t raw;
} clock_clk_sys_ctrl_t;

typedef union {
  struct {
    uint32_t frac : 8;
    uint32_t integer : 24;
  };
  uint32_t raw;
} clock_clk_sys_div_t;

typedef union {
  struct {
    uint32_t slice : 32;
  };
  uint32_t raw;
} clock_clk_sys_selected_t;

typedef union {
  struct {
    uint32_t : 5;
    uint32_t auxsrc : 3;
    uint32_t : 2;
    uint32_t kill : 1;
    uint32_t enable : 1;
    uint32_t : 20;
  };
  uint32_t raw;
} clock_clk_peri_ctrl_t;

typedef union {
  struct {
    uint32_t slice : 32;
  };
  uint32_t raw;
} clock_clk_peri_selected_t;

typedef union {
  struct {
    uint32_t : 5;
    uint32_t auxsrc : 3;
    uint32_t : 2;
    uint32_t kill : 1;
    uint32_t enable : 1;
    uint32_t : 4;
    uint32_t phase : 2;
    uint32_t : 2;
    uint32_t nudge : 1;
    uint32_t : 11;
  };
  uint32_t raw;
} clock_clk_usb_ctrl_t;

typedef union {
  struct {
    uint32_t : 8;
    uint32_t integer : 2;
    uint32_t : 22;
  };
  uint32_t raw;
} clock_clk_usb_div_t;

typedef union {
  struct {
    uint32_t slice : 32;
  };
  uint32_t raw;
} clock_clk_usb_selected_t;

typedef union {
  struct {
    uint32_t : 5;
    uint32_t auxsrc : 3;
    uint32_t : 2;
    uint32_t kill : 1;
    uint32_t enable : 1;
    uint32_t : 4;
    uint32_t phase : 2;
    uint32_t : 2;
    uint32_t nudge : 1;
    uint32_t : 11;
  };
  uint32_t raw;
} clock_clk_adc_ctrl_t;

typedef union {
  struct {
    uint32_t : 8;
    uint32_t integer : 2;
    uint32_t : 22;
  };
  uint32_t raw;
} clock_clk_adc_div_t;

typedef union {
  struct {
    uint32_t slice : 32;
  };
  uint32_t raw;
} clock_clk_adc_selected_t;

typedef union {
  struct {
    uint32_t : 5;
    uint32_t auxsrc : 3;
    uint32_t : 2;
    uint32_t kill : 1;
    uint32_t enable : 1;
    uint32_t : 4;
    uint32_t phase : 2;
    uint32_t : 2;
    uint32_t nudge : 1;
    uint32_t : 11;
  };
  uint32_t raw;
} clock_clk_rtc_ctrl_t;

typedef union {
  struct {
    uint32_t frac : 8;
    uint32_t integer : 24;
  };
  uint32_t raw;
} clock_clk_rtc_div_t;

typedef union {
  struct {
    uint32_t slice : 32;
  };
  uint32_t raw;
} clock_clk_rtc_selected_t;

typedef union {
  struct {
    uint32_t timeout : 8;
    uint32_t enable : 1;
    uint32_t : 3;
    uint32_t frce : 1;
    uint32_t : 3;
    uint32_t clear : 1;
    uint32_t : 15;
  };
  uint32_t raw;
} clock_clk_sys_resus_ctrl_t;

typedef union {
  struct {
    uint32_t resussed : 1;
    uint32_t : 31;
  };
  uint32_t raw;
} clock_clk_sys_resus_status_t;

typedef union {
  struct {
    uint32_t freq : 20;
    uint32_t : 12;
  };
  uint32_t raw;
} clock_fc0_ref_khz_t;

typedef union {
  struct {
    uint32_t freq : 25;
    uint32_t : 7;
  };
  uint32_t raw;
} clock_fc0_min_khz_t;

typedef union {
  struct {
    uint32_t freq : 25;
    uint32_t : 7;
  };
  uint32_t raw;
} clock_fc0_max_khz_t;

typedef union {
  struct {
    uint32_t delay : 3;
    uint32_t : 29;
  };
  uint32_t raw;
} clock_fc0_delay_t;

typedef union {
  struct {
    uint32_t interval : 4;
    uint32_t : 28;
  };
  uint32_t raw;
} clock_fc0_interval_t;

typedef union {
  struct {
    uint32_t src : 8;
    uint32_t : 24;
  };
  uint32_t raw;
} clock_fc0_src_t;

typedef union {
  struct {
    uint32_t pass : 1;
    uint32_t : 3;
    uint32_t done : 1;
    uint32_t : 3;
    uint32_t running : 1;
    uint32_t : 3;
    uint32_t waiting : 1;
    uint32_t : 3;
    uint32_t fail : 1;
    uint32_t : 3;
    uint32_t slow : 1;
    uint32_t : 3;
    uint32_t fast : 1;
    uint32_t : 3;
    uint32_t died : 1;
    uint32_t : 3;
  };
  uint32_t raw;
} clock_fc0_status_t;

typedef union {
  struct {
    uint32_t frac : 5;
    uint32_t khz : 25;
    uint32_t : 2;
  };
  uint32_t raw;
} clock_fc0_result_t;

typedef union {
  struct {
    uint32_t clk_sys_clocks : 1;
    uint32_t clk_adc_adc : 1;
    uint32_t clk_sys_adc : 1;
    uint32_t clk_sys_busctrl : 1;
    uint32_t clk_sys_busfabric : 1;
    uint32_t clk_sys_dma : 1;
    uint32_t clk_sys_i2c0 : 1;
    uint32_t clk_sys_i2c1 : 1;
    uint32_t clk_sys_io : 1;
    uint32_t clk_sys_jtag : 1;
    uint32_t clk_sys_vreg_and_chip_reset : 1;
    uint32_t clk_sys_pads : 1;
    uint32_t clk_sys_pio0 : 1;
    uint32_t clk_sys_pio1 : 1;
    uint32_t clk_sys_pll_sys : 1;
    uint32_t clk_sys_pll_usb : 1;
    uint32_t clk_sys_psm : 1;
    uint32_t clk_sys_pwm : 1;
    uint32_t clk_sys_resets : 1;
    uint32_t clk_sys_rom : 1;
    uint32_t clk_sys_rosc : 1;
    uint32_t clk_rtc_rtc : 1;
    uint32_t clk_sys_rtc : 1;
    uint32_t clk_sys_sio : 1;
    uint32_t clk_peri_spi0 : 1;
    uint32_t clk_sys_spi0 : 1;
    uint32_t clk_peri_spi1 : 1;
    uint32_t clk_sys_spi1 : 1;
    uint32_t clk_sys_sram0 : 1;
    uint32_t clk_sys_sram1 : 1;
    uint32_t clk_sys_sram2 : 1;
    uint32_t clk_sys_sram3 : 1;
  };
  uint32_t raw;
} clock_wake_en0_t;

typedef union {
  struct {
    uint32_t clk_sys_sram4 : 1;
    uint32_t clk_sys_sram5 : 1;
    uint32_t clk_sys_syscfg : 1;
    uint32_t clk_sys_sysinfo : 1;
    uint32_t clk_sys_tbman : 1;
    uint32_t clk_sys_timer : 1;
    uint32_t clk_peri_uart0 : 1;
    uint32_t clk_sys_uart0 : 1;
    uint32_t clk_peri_uart1 : 1;
    uint32_t clk_sys_uart1 : 1;
    uint32_t clk_sys_usbctrl : 1;
    uint32_t clk_usb_usbctrl : 1;
    uint32_t clk_sys_watchdog : 1;
    uint32_t clk_sys_xip : 1;
    uint32_t clk_sys_xosc : 1;
    uint32_t : 17;
  };
  uint32_t raw;
} clock_wake_en1_t;

typedef union {
  struct {
    uint32_t clk_sys_clocks : 1;
    uint32_t clk_adc_adc : 1;
    uint32_t clk_sys_adc : 1;
    uint32_t clk_sys_busctrl : 1;
    uint32_t clk_sys_busfabric : 1;
    uint32_t clk_sys_dma : 1;
    uint32_t clk_sys_i2c0 : 1;
    uint32_t clk_sys_i2c1 : 1;
    uint32_t clk_sys_io : 1;
    uint32_t clk_sys_jtag : 1;
    uint32_t clk_sys_vreg_and_chip_reset : 1;
    uint32_t clk_sys_pads : 1;
    uint32_t clk_sys_pio0 : 1;
    uint32_t clk_sys_pio1 : 1;
    uint32_t clk_sys_pll_sys : 1;
    uint32_t clk_sys_pll_usb : 1;
    uint32_t clk_sys_psm : 1;
    uint32_t clk_sys_pwm : 1;
    uint32_t clk_sys_resets : 1;
    uint32_t clk_sys_rom : 1;
    uint32_t clk_sys_rosc : 1;
    uint32_t clk_rtc_rtc : 1;
    uint32_t clk_sys_rtc : 1;
    uint32_t clk_sys_sio : 1;
    uint32_t clk_peri_spi0 : 1;
    uint32_t clk_sys_spi0 : 1;
    uint32_t clk_peri_spi1 : 1;
    uint32_t clk_sys_spi1 : 1;
    uint32_t clk_sys_sram0 : 1;
    uint32_t clk_sys_sram1 : 1;
    uint32_t clk_sys_sram2 : 1;
    uint32_t clk_sys_sram3 : 1;
  };
  uint32_t raw;
} clock_sleep_en0_t;

typedef union {
  struct {
    uint32_t clk_sys_sram4 : 1;
    uint32_t clk_sys_sram5 : 1;
    uint32_t clk_sys_syscfg : 1;
    uint32_t clk_sys_sysinfo : 1;
    uint32_t clk_sys_tbman : 1;
    uint32_t clk_sys_timer : 1;
    uint32_t clk_peri_uart0 : 1;
    uint32_t clk_sys_uart0 : 1;
    uint32_t clk_peri_uart1 : 1;
    uint32_t clk_sys_uart1 : 1;
    uint32_t clk_sys_usbctrl : 1;
    uint32_t clk_usb_usbctrl : 1;
    uint32_t clk_sys_watchdog : 1;
    uint32_t clk_sys_xip : 1;
    uint32_t clk_sys_xosc : 1;
    uint32_t : 17;
  };
  uint32_t raw;
} clock_sleep_en1_t;

typedef union {
  struct {
    uint32_t clk_sys_clocks : 1;
    uint32_t clk_adc_adc : 1;
    uint32_t clk_sys_adc : 1;
    uint32_t clk_sys_busctrl : 1;
    uint32_t clk_sys_busfabric : 1;
    uint32_t clk_sys_dma : 1;
    uint32_t clk_sys_i2c0 : 1;
    uint32_t clk_sys_i2c1 : 1;
    uint32_t clk_sys_io : 1;
    uint32_t clk_sys_jtag : 1;
    uint32_t clk_sys_vreg_and_chip_reset : 1;
    uint32_t clk_sys_pads : 1;
    uint32_t clk_sys_pio0 : 1;
    uint32_t clk_sys_pio1 : 1;
    uint32_t clk_sys_pll_sys : 1;
    uint32_t clk_sys_pll_usb : 1;
    uint32_t clk_sys_psm : 1;
    uint32_t clk_sys_pwm : 1;
    uint32_t clk_sys_resets : 1;
    uint32_t clk_sys_rom : 1;
    uint32_t clk_sys_rosc : 1;
    uint32_t clk_rtc_rtc : 1;
    uint32_t clk_sys_rtc : 1;
    uint32_t clk_sys_sio : 1;
    uint32_t clk_peri_spi0 : 1;
    uint32_t clk_sys_spi0 : 1;
    uint32_t clk_peri_spi1 : 1;
    uint32_t clk_sys_spi1 : 1;
    uint32_t clk_sys_sram0 : 1;
    uint32_t clk_sys_sram1 : 1;
    uint32_t clk_sys_sram2 : 1;
    uint32_t clk_sys_sram3 : 1;
  };
  uint32_t raw;
} clock_enabled0_t;

typedef union {
  struct {
    uint32_t clk_sys_sram4 : 1;
    uint32_t clk_sys_sram5 : 1;
    uint32_t clk_sys_syscfg : 1;
    uint32_t clk_sys_sysinfo : 1;
    uint32_t clk_sys_tbman : 1;
    uint32_t clk_sys_timer : 1;
    uint32_t clk_peri_uart0 : 1;
    uint32_t clk_sys_uart0 : 1;
    uint32_t clk_peri_uart1 : 1;
    uint32_t clk_sys_uart1 : 1;
    uint32_t clk_sys_usbctrl : 1;
    uint32_t clk_usb_usbctrl : 1;
    uint32_t clk_sys_watchdog : 1;
    uint32_t clk_sys_xip : 1;
    uint32_t clk_sys_xosc : 1;
    uint32_t : 17;
  };
  uint32_t raw;
} clock_enabled1_t;

typedef union {
  struct {
    uint32_t clk_sys_resus : 1;
    uint32_t : 31;
  };
  uint32_t raw;
} clock_intr_t;

typedef union {
  struct {
    uint32_t clk_sys_resus : 1;
    uint32_t : 31;
  };
  uint32_t raw;
} clock_inte_t;

typedef union {
  struct {
    uint32_t clk_sys_resus : 1;
    uint32_t : 31;
  };
  uint32_t raw;
} clock_intf_t;

typedef union {
  struct {
    uint32_t clk_sys_resus : 1;
    uint32_t : 31;
  };
  uint32_t raw;
} clock_ints_t;

#define CLOCK_CLK_GPOUT0_CTRL                                                  \
  (*(volatile clock_clk_gpout_ctrl_t *)(CLOCK_BASE + 0x00))
#define CLOCK_CLK_GPOUT0_DIV                                                   \
  (*(volatile clock_clk_gpout_div_t *)(CLOCK_BASE + 0x04))
#define CLOCK_CLK_GPOUT0_SELECTED                                              \
  (*(volatile clock_clk_gpout_selected_t *)(CLOCK_BASE + 0x08))
#define CLOCK_CLK_GPOUT1_CTRL                                                  \
  (*(volatile clock_clk_gpout_ctrl_t *)(CLOCK_BASE + 0x0c))
#define CLOCK_CLK_GPOUT1_DIV                                                   \
  (*(volatile clock_clk_gpout_div_t *)(CLOCK_BASE + 0x10))
#define CLOCK_CLK_GPOUT1_SELECTED                                              \
  (*(volatile clock_clk_gpout_selected_t *)(CLOCK_BASE + 0x14))
#define CLOCK_CLK_GPOUT2_CTRL                                                  \
  (*(volatile clock_clk_gpout_ctrl_t *)(CLOCK_BASE + 0x18))
#define CLOCK_CLK_GPOUT2_DIV                                                   \
  (*(volatile clock_clk_gpout_div_t *)(CLOCK_BASE + 0x1c))
#define CLOCK_CLK_GPOUT2_SELECTED                                              \
  (*(volatile clock_clk_gpout_selected_t *)(CLOCK_BASE + 0x20))
#define CLOCK_CLK_GPOUT3_CTRL                                                  \
  (*(volatile clock_clk_gpout_ctrl_t *)(CLOCK_BASE + 0x24))
#define CLOCK_CLK_GPOUT3_DIV                                                   \
  (*(volatile clock_clk_gpout_div_t *)(CLOCK_BASE + 0x28))
#define CLOCK_CLK_GPOUT3_SELECTED                                              \
  (*(volatile clock_clk_gpout_selected_t *)(CLOCK_BASE + 0x2c))
#define CLOCK_CLK_REF_CTRL                                                     \
  (*(volatile clock_clk_ref_ctrl_t *)(CLOCK_BASE + 0x30))
#define CLOCK_CLK_REF_DIV (*(volatile clock_clk_ref_div_t *)(CLOCK_BASE + 0x34))
#define CLOCK_CLK_REF_SELECTED                                                 \
  (*(volatile clock_clk_ref_selected_t *)(CLOCK_BASE + 0x38))
#define CLOCK_CLK_SYS_CTRL                                                     \
  (*(volatile clock_clk_sys_ctrl_t *)(CLOCK_BASE + 0x3c))
#define CLOCK_CLK_SYS_DIV (*(volatile clock_clk_sys_div_t *)(CLOCK_BASE + 0x40))
#define CLOCK_CLK_SYS_SELECTED                                                 \
  (*(volatile clock_clk_sys_selected_t *)(CLOCK_BASE + 0x44))
#define CLOCK_CLK_PERI_CTRL                                                    \
  (*(volatile clock_clk_peri_ctrl_t *)(CLOCK_BASE + 0x48))
#define CLOCK_CLK_PERI_SELECTED                                                \
  (*(volatile clock_clk_peri_selected_t *)(CLOCK_BASE + 0x50))
#define CLOCK_CLK_USB_CTRL                                                     \
  (*(volatile clock_clk_usb_ctrl_t *)(CLOCK_BASE + 0x54))
#define CLOCK_CLK_USB_DIV (*(volatile clock_clk_usb_div_t *)(CLOCK_BASE + 0x58))
#define CLOCK_CLK_USB_SELECTED                                                 \
  (*(volatile clock_clk_usb_selected_t *)(CLOCK_BASE + 0x5c))
#define CLOCK_CLK_ADC_CTRL                                                     \
  (*(volatile clock_clk_adc_ctrl_t *)(CLOCK_BASE + 0x60))
#define CLOCK_CLK_ADC_DIV (*(volatile clock_clk_adc_div_t *)(CLOCK_BASE + 0x64))
#define CLOCK_CLK_ADC_SELECTED                                                 \
  (*(volatile clock_clk_adc_selected_t *)(CLOCK_BASE + 0x68))
#define CLOCK_CLK_RTC_CTRL                                                     \
  (*(volatile clock_clk_rtc_ctrl_t *)(CLOCK_BASE + 0x6c))
#define CLOCK_CLK_RTC_DIV (*(volatile clock_clk_rtc_div_t *)(CLOCK_BASE + 0x70))
#define CLOCK_CLK_RTC_SELECTED                                                 \
  (*(volatile clock_clk_rtc_selected_t *)(CLOCK_BASE + 0x74))
#define CLOCK_CLK_SYS_RESUS_CTRL                                               \
  (*(volatile clock_clk_sys_resus_ctrl_t *)(CLOCK_BASE + 0x78))
#define CLOCK_CLK_SYS_RESUS_STATUS                                             \
  (*(volatile clock_clk_sys_resus_status_t *)(CLOCK_BASE + 0x7c))
#define CLOCK_FC0_REF_KHZ (*(volatile clock_fc0_ref_khz_t *)(CLOCK_BASE + 0x80))
#define CLOCK_FC0_MIN_KHZ (*(volatile clock_fc0_min_khz_t *)(CLOCK_BASE + 0x84))
#define CLOCK_FC0_MAX_KHZ (*(volatile clock_fc0_max_khz_t *)(CLOCK_BASE + 0x88))
#define CLOCK_FC0_DELAY (*(volatile clock_fc0_delay_t *)(CLOCK_BASE + 0x8c))
#define CLOCK_FC0_INTERVAL                                                     \
  (*(volatile clock_fc0_interval_t *)(CLOCK_BASE + 0x90))
#define CLOCK_FC0_SRC (*(volatile clock_fc0_src_t *)(CLOCK_BASE + 0x94))
#define CLOCK_FC0_STATUS (*(volatile clock_fc0_status_t *)(CLOCK_BASE + 0x98))
#define CLOCK_FC0_RESULT (*(volatile clock_fc0_result_t *)(CLOCK_BASE + 0x9c))
#define CLOCK_WAKE_EN0 (*(volatile clock_wake_en0_t *)(CLOCK_BASE + 0xa0))
#define CLOCK_WAKE_EN1 (*(volatile clock_wake_en1_t *)(CLOCK_BASE + 0xa4))
#define CLOCK_SLEEP_EN0 (*(volatile clock_sleep_en0_t *)(CLOCK_BASE + 0xa8))
#define CLOCK_SLEEP_EN1 (*(volatile clock_sleep_en1_t *)(CLOCK_BASE + 0xac))
#define CLOCK_ENABLED0 (*(volatile clock_enabled0_t *)(CLOCK_BASE + 0xb0))
#define CLOCK_ENABLED1 (*(volatile clock_enabled1_t *)(CLOCK_BASE + 0xb4))
#define CLOCK_INTR (*(volatile clock_intr_t *)(CLOCK_BASE + 0xb8))
#define CLOCK_INTE (*(volatile clock_inte_t *)(CLOCK_BASE + 0xbc))
#define CLOCK_INTF (*(volatile clock_intf_t *)(CLOCK_BASE + 0xc0))
#define CLOCK_INTS (*(volatile clock_ints_t *)(CLOCK_BASE + 0xc4))
