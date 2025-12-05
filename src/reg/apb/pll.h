//
// PLL_SYS
// PLL_USB
//

#pragma once

#include <stdint.h>

#define PLL_SYS_BASE 0x40028000
#define PLL_USB_BASE 0x4002c000

// 0x0
typedef union {
  struct {
    uint32_t refdiv : 6;
    uint32_t : 2;
    uint32_t bypass : 1;
    uint32_t : 22;
    uint32_t lock : 1;
  };
  uint32_t raw;
} pll_cs_t;

// 0x4
typedef union {
  struct {
    uint32_t pd : 1;
    uint32_t : 1;
    uint32_t dsmpd : 1;
    uint32_t postdivpd : 1;
    uint32_t : 1;
    uint32_t vcopd : 1;
    uint32_t : 26;
  };
  uint32_t raw;
} pll_pwr_t;

// 0x8
typedef union {
  struct {
    uint32_t ctrl : 12;
    uint32_t : 20;
  };
  uint32_t raw;
} pll_fbvdiv_int_t;

// 0xc
typedef union {
  struct {
    uint32_t : 12;
    uint32_t postdiv2 : 3;
    uint32_t : 1;
    uint32_t postdiv1 : 3;
    uint32_t : 13;
  };
  uint32_t raw;
} pll_prim_t;

#define PLL_SYS_CS (*(volatile pll_cs_t *)(PLL_SYS_BASE + 0x0))
#define PLL_SYS_PWR (*(volatile pll_pwr_t *)(PLL_SYS_BASE + 0x4))
#define PLL_SYS_FBDIV_INT (*(volatile pll_fbvdiv_int_t *)(PLL_SYS_BASE + 0x8))
#define PLL_SYS_PRIM (*(volatile pll_prim_t *)(PLL_SYS_BASE + 0xc))

#define PLL_USB_CS (*(volatile pll_cs_t *)(PLL_USB_BASE + 0x0))
#define PLL_USB_PWR (*(volatile pll_pwr_t *)(PLL_USB_BASE + 0x4))
#define PLL_USB_FBDIV_INT (*(volatile pll_fbvdiv_int_t *)(PLL_USB_BASE + 0x8))
#define PLL_USB_PRIM (*(volatile pll_prim_t *)(PLL_USB_BASE + 0xc))
