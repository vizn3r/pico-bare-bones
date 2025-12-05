//
// XOSC_BASE
//

#pragma once

#include <stdint.h>

#define XOSC_BASE 0x40024000

// 0x0
typedef union {
  struct {
    // cannot be changed, default to XOSC_CTRL_FREQ_1_15MHz
    uint32_t freq_range : 12;
    uint32_t enable : 12;
    uint32_t : 8;
  };
  uint32_t raw;
} xosc_ctrl_t;

#define XOSC_CTRL_ENABLE (uint16_t)0xfab
#define XOSC_CTRL_DISABLE (uint16_t)0xd1e

#define XOSC_CTRL_FREQ_1_15MHz (uint32_t)0xaa0

// 0x04
typedef union {
  struct {
    uint32_t freq_range : 2;
    uint32_t : 10;
    uint32_t enabled : 1;
    uint32_t : 11;
    uint32_t badwrite : 1;
    uint32_t : 6;
    uint32_t stable : 1;
  };
  uint32_t raw;
} xosc_status_t;

// 0x08
#define XOSC_DORMANT_DORMANT 0x636f6d61
#define XOSC_DORMANT_WAKE 0x77616b65

// 0x0c
typedef union {
  struct {
    uint32_t delay : 14;
    uint32_t : 6;
    uint32_t x4 : 1;
    uint32_t : 11;
  };
  uint32_t raw;
} xosc_startup_t;

// 0x1c
typedef union {
  struct {
    uint32_t count : 8;
    uint32_t : 24;
  };
  uint32_t raw;
} xosc_count_t;

#define XOSC_CTRL (*(volatile xosc_ctrl_t *)(XOSC_BASE + 0x00))
#define XOSC_STATUS (*(volatile xosc_status_t *)(XOSC_BASE + 0x04))
#define XOSC_DORMANT (*(volatile uint32_t *)(XOSC_BASE + 0x08))
#define XOSC_STARTUP (*(volatile xosc_startup_t *)(XOSC_BASE + 0x0c))
#define XOSC_COUNT (*(volatile uint32_t *)(XOSC_BASE + 0x1c))
