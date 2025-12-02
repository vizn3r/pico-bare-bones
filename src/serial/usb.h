#pragma once

// Base registers
#define S_USB_CTRL_BASE 0x50100000
#define S_USB_DPSRAM_BASE 0x50100000
#define S_USB_REGS_BASE 0x50110000

// DPSRAM layout
#define S_USB_DPSRAM_SETUP_PACKET (S_USB_DPSRAM_BASE + 0x0)

#define S_USB_DPSRAM_EP_IN_CTRL(EP_NUM)                                        \
  (S_USB_DPSRAM_BASE + (EP_NUM * 8) + 0x08)
#define S_USB_DPSRAM_EP_OUT_CTRL(EP_NUM)                                       \
  (S_USB_DPSRAM_BASE + (EP_NUM * 8) + 0xc)

#define S_USB_DPSRAM_EP_IN_BUFF_CTRL(EP_NUM)                                   \
  (S_USB_DPSRAM_BASE + (EP_NUM * 8) + 0x80)
#define S_USB_DPSRAM_EP_OUT_BUFF_CTRL(EP_NUM)                                  \
  (S_USB_DPSRAM_BASE + (EP_NUM * 8) + 0x84)
