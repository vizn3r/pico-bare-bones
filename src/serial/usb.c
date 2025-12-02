#include "../regs/usb.h"
#include "../regs/gpio.h"
#include "usb.h"
#include <stdint.h>
#include <sys/types.h>

uint8_t s_usb_cdc_recv_buff[64];
uint16_t s_usb_cdc_recv_buff_len;

static uint8_t ep0_data_toggle = 0;
static uint8_t ep2_in_data_toggle = 0;
static volatile uint8_t configured = 0;
static volatile uint8_t pending_address = 0;

void s_usb_init_blocking(void) {
  __asm volatile("cpsie i");

  // Start XOSC
  *(volatile uint32_t *)0x4002400C = 47;       // STARTUP delay
  *(volatile uint32_t *)0x40024000 = 0xFABAA0; // CTRL: enable
  while (!(*(volatile uint32_t *)0x40024004 & 0x80000000))
    ;

  // Reset PLL_USB
  *(volatile uint32_t *)0x4000E000 = (1 << 13); // Atomic set (assert reset)
  *(volatile uint32_t *)0x4000F000 =
      (1 << 13); // Atomic clear (release reset)  while (!(*(volatile uint32_t
                 // *)0x4000C008 & (1 << 13)))
  ;

  // PLL config
  *(volatile uint32_t *)0x4002C004 = 0x29;
  *(volatile uint32_t *)0x4002C000 = 1;
  *(volatile uint32_t *)0x4002C008 = 40;
  *(volatile uint32_t *)0x4002C004 = 0x20;

  while (!(*(volatile uint32_t *)0x4002C000 & 0x80000000))
    ;

  *(volatile uint32_t *)0x4002C00C = (5 << 16) | (2 << 12);
  *(volatile uint32_t *)0x4002C004 = 0;

  // USB clock
  *(volatile uint32_t *)0x40008058 =
      (1 << 8); // DIV = 1 (integer part at bits 8+)
  *(volatile uint32_t *)0x40008054 = (1 << 11); // ENABLE

  // Unreset USB - use atomic clear register
  *(volatile uint32_t *)0x4000F000 = (1 << 24); // RESETS atomic clear
  while (!(*(volatile uint32_t *)0x4000C008 & (1 << 24)))
    ;

  // Clear DPSRAM
  for (int i = 0; i < 4096; i += 4) {
    *(volatile uint32_t *)(S_USB_DPSRAM_BASE + i) = 0;
  }

  // USB setup
  *(volatile uint32_t *)(S_USB_REGS_BASE + 0x40) = 0;
  *(volatile uint32_t *)(S_USB_REGS_BASE + 0x74) = (1 << 0) | (1 << 3);
  *(volatile uint32_t *)(S_USB_REGS_BASE + 0x78) = (1 << 2) | (1 << 3);
  *(volatile uint32_t *)(S_USB_REGS_BASE + 0x40) = 1;

  S_USB_DPSRAM_EP_IN_CTRL(1) = (1 << 31) | (3 << 26) | (0x140 >> 6);
  S_USB_DPSRAM_EP_OUT_CTRL(2) = (1 << 31) | (2 << 26) | (0x180 >> 6);
  S_USB_DPSRAM_EP_IN_CTRL(2) = (1 << 31) | (2 << 26) | (0x1C0 >> 6);

  *(volatile uint32_t *)(S_USB_REGS_BASE + 0x90) =
      (1 << 16) | (1 << 4) | (1 << 12);
  *(volatile uint32_t *)(S_USB_REGS_BASE + 0x4c) = (1 << 16);

  *(volatile uint32_t *)(S_USB_DPSRAM_BASE + 0x84) = 64;
  *(volatile uint32_t *)(S_USB_DPSRAM_BASE + 0x1000 + 0x84) = (1 << 10);

  *(volatile uint32_t *)0xE000E100 = (1 << 5);
}

void s_usb_irq_handle(void) {
  if (S_USB_REG_INTS.setup_req) {
    volatile uint8_t *setup = (volatile uint8_t *)S_USB_DPSRAM_SETUP_PACKET;

    s_usb_setup_packet_t *packet = (s_usb_setup_packet_t *)setup;

    uint8_t desc_type;
    uint8_t desc_index;

    volatile uint8_t *ep0_in_buf;
    uint16_t len;

    const uint8_t *str_desc;
    uint16_t str_len;

    switch (packet->bRequest) {
    case 0x05: // SET_ADDRESS
      pending_address = packet->wValue & 0x7F;
      // Send ZLP, address is set after status stage completes
      ep0_data_toggle = 1;
      S_USB_DPSRAM_EP_IN_BUFF_CTRL(0) = (1 << 13) | (1 << 15) | (1 << 10);
      break;
    case 0x06: // SET_DESCRIPTOR
      desc_type = (packet->wValue >> 8) & 0xFF;
      desc_index = packet->wValue & 0xFF;

      switch (desc_type) {
      case 0x01: // Device descriptor
        len = sizeof(device_descriptor);
        if (len > packet->wLength)
          len = packet->wLength;

        volatile uint8_t *ep0_in_buf =
            (volatile uint8_t *)(S_USB_DPSRAM_BASE + 0x100);
        for (int i = 0; i < len; i++) {
          ep0_in_buf[i] = device_descriptor[i];
        }

        ep0_data_toggle = 1;
        S_USB_DPSRAM_EP_IN_BUFF_CTRL(0) =
            len | (1 << 13) | (1 << 15) | (1 << 10);
        break;
      case 0x02:
        len = sizeof(config_descriptor);
        if (len > packet->wLength)
          len = packet->wLength;

        ep0_in_buf = (volatile uint8_t *)(S_USB_DPSRAM_BASE + 0x100);

        for (int i = 0; i < len; i++) {
          ep0_in_buf[i] = config_descriptor[i];
        }

        // full 15 bit, avaliable in bit 31
        S_USB_DPSRAM_EP_IN_BUFF_CTRL(0) = len | (1 << 15) | (1 << 31);

        break;
      case 0x03:
        switch (desc_index) {
        case 0:
          str_desc = string_descriptor_0;
          str_len = sizeof(string_descriptor_0);
          break;
        case 1:
          str_desc = string_descriptor_1;
          str_len = sizeof(string_descriptor_1);
          break;
        case 2:
          str_desc = string_descriptor_2;
          str_len = sizeof(string_descriptor_2);
          break;
        default:
          return;
        }

        if (str_len > packet->wLength)
          str_len = packet->wLength;

        ep0_in_buf = (volatile uint8_t *)(S_USB_DPSRAM_BASE + 0x100);

        for (int i = 0; i < str_len; i++) {
          ep0_in_buf[i] = str_desc[i];
        }

        S_USB_DPSRAM_EP_IN_BUFF_CTRL(0) = str_len | (1 << 15) | (1 << 31);
        break;
      }
      break;
    case 0x09: // SET_CONFIGURATION
      configured = 1;
      // Arm EP2 OUT for receiving data
      S_USB_DPSRAM_EP_OUT_BUFF_CTRL(2) = 64 | (1 << 10);
      // Send ZLP status
      ep0_data_toggle = 1;
      S_USB_DPSRAM_EP_IN_BUFF_CTRL(0) = (1 << 13) | (1 << 15) | (1 << 10);
      break;
    default:
      break;
    }
    S_USB_REG_SIE_STATUS.setup_rec = 1;
  }

  if (S_USB_REG_INTS.buff_status) {
    uint32_t buffers = S_USB_REG_BUFF_STATUS.raw;

    S_USB_REG_BUFF_STATUS.raw = buffers;

    if (buffers & (1 << 0)) {
      // EP0 IN completed
      if (pending_address) {
        S_USB_REG_ADDR_ENDP.address = pending_address;
        pending_address = 0;
      }
    }
    if (buffers & (1 << 2)) {
      // interrupt done sending
    }
    if (buffers & (1 << 4)) {
      // receive
      s_usb_cdc_recv_buff_len = s_usb_cdc_recv(s_usb_cdc_recv_buff, 64);
    }
    if (buffers & (1 << 5)) {
      // bulk in finished sending
    }
  }

  if (S_USB_REG_INTS.bus_reset) {
    S_USB_REG_ADDR_ENDP.address = 0;
    configured = 0;
    pending_address = 0;
    ep0_data_toggle = 0;
    ep2_in_data_toggle = 0;
    S_USB_REG_SIE_STATUS.bus_reset = 1;
  }
}

void s_usb_cdc_send(const uint8_t *data, uint16_t len) {
  if (!configured || len > 64)
    return;
  if (len > 64)
    len = 64;

  volatile uint8_t *ep2_in_buf =
      (volatile uint8_t *)(S_USB_DPSRAM_BASE + 0x1C0);

  for (int i = 0; i < len; i++) {
    ep2_in_buf[i] = data[i];
  }

  uint32_t buf_ctrl = len | (1 << 15) | (1 << 10);
  if (ep2_in_data_toggle) {
    buf_ctrl |= (1 << 13);
  }
  ep2_in_data_toggle ^= 1;

  S_USB_DPSRAM_EP_IN_BUFF_CTRL(2) = buf_ctrl;
}

uint16_t s_usb_cdc_recv(uint8_t *data, uint16_t max_len) {
  volatile uint8_t *ep2_out_buf =
      (volatile uint8_t *)(S_USB_DPSRAM_BASE + 0x140);

  uint16_t len = S_USB_DPSRAM_EP_OUT_BUFF_CTRL(2) & 0x3FF;
  if (len > max_len)
    len = max_len;

  for (int i = 0; i < len; i++) {
    data[i] = ep2_out_buf[i];
  }

  S_USB_DPSRAM_EP_OUT_BUFF_CTRL(2) = 64 | (1 << 15) | (1 << 31);

  return len;
}
