#pragma once

/* NOTES from docs
 *
 *
 *  4.1.2.7.1. Concurrent access
 *
 * The AVAILABLE bit in the buffer control register is used to indicate who
 * has ownership of a buffer. This bit should be set to 1 by the processor to
 * give the controller ownership of the buffer. The controller will set the bit
 * back to 0 when it has used the buffer.
 *
 * correct process:
 * write buff info to buff ctrl reg
 * nop for some clk_sys to ensure one clk_usb passed
 * set AVAILABLE bit
 *
 *
 *
 *
 */

#define _USB_BASE(offset) (0x50100000 + offset)

int rp_usb_init(void);
