.syntax unified
.cpu cortex-m0plus
.thumb

.section .boot2, "ax"

#define SSI_BASE      0x18000000
#define QSPI_PAD      0x40020000
#define PPB_BASE      0xE0000000
#define APP_BASE      0x10000100
#define VTOR          0xED08

.global _stage2_boot
.type _stage2_boot,%function
.thumb_func
_stage2_boot:
  ldr r0, =QSPI_PAD
  movs r1, #(2 << 4 | 1) // set DRIVE to 8MA and SLEWFAST to fast
  str r1, [r0, #0x04]

  ldr r2, [r0, #0x08] // Take the current SD0 config
  movs r1, #2 // bitmask for Schmitt
  bics r2, r1
  str r2, [r0, #0x08]
  str r2, [r0, #0x0c]
  str r2, [r0, #0x10]
  str r2, [r0, #0x14]

  // Disable SSI
  ldr r0, =SSI_BASE
  movs r1, #0
  str r1, [r0, #0x08]

  // Setup BAUD
  movs r1, #4
  str r1, [r0, #0x14]

  // RX sample delay
  movs r1, #1
  movs r2, #0xf0
  str r1, [r0, r2]

flash_setup:
  // CTRL0 for normal SPI R/W
  ldr r1, =(7 << 16 | 0x0 << 8) // 8 bits per data frame, RX and TX mode
  str r1, [r0, #0]

  // Enable SSI
  movs r1, #1
  str r1, [r0, #0x08]

  movs r1, #0x35 // status register 2

  // read flash
  str r1, [r0, #0x60] // write to SSI data register
  str r1, [r0, #0x60] // dummy byte

  bl wait_for_ssi

  ldr r1, [r0, #0x60] // discard first byte
  ldr r1, [r0, #0x60]
  // end read

  movs r2, #0b10 // QE bit
  tst r1, r2
  bne skip_flash_setup

  movs r1, #0x06 // write enable cmd
  str r1, [r0, #0x60]

  bl wait_for_ssi
  ldr r1, [r0, #0x60] // discard

  // write status
  movs r1, #0x01 // status register 1
  str r1, [r0, #0x60]
  movs r3, #0
  // write to sr1+2
  str r3, [r0, #0x60] // register 1 data
  str r2, [r0, #0x60] // register 2 data

  bl wait_for_ssi

  ldr r1, [r0, #0x60]
  ldr r1, [r0, #0x60]
  ldr r1, [r0, #0x60]

  // poll status register for completion
  1:
    movs r1, #0x05 // read status register 1
    // read flash
    str r1, [r0, #0x60] // write to SSI data register
    str r1, [r0, #0x60] // dummy byte

    bl wait_for_ssi
      
    ldr r3, [r0, #0x60] // discard first byte
    ldr r3, [r0, #0x60]
  
    movs r2, #1
    tst r3, r2
    bne 1b

skip_flash_setup:
  // disable SSI
  movs r1, #0
  str r1, [r0, #0x08]

  // setup CTRL0
  ldr r1, =(31 << 16 | 0x3 << 8 | 0x2 << 21) // 32 bit dfs, EEPROM read mode, QSPI frf
  str r1, [r0, #0]

  // setup CTRL1
  movs r1, #0x0
  str r1, [r0, #0x04] // NDF 0

  // setup initial SPI_CTRL0
  ldr r1, =(8 << 2 | 4 << 11 | 0x2 << 8 | 0x1) // 8 bit addr len, 4 wait cycles, 8 bit instruction len, 1c2a trans type 
  movs r2, #0xf4
  str r1, [r0, r2]

  // enable SSI
  movs r1, #1
  str r1, [r0, #0x08]

  // dummy data
  ldr r1, =0xEB
  str r1, [r0, #0x60]
  ldr r1, =0xA0 // wrap for continuous read
  str r1, [r0, #0x60] // should trigger the transaction

  bl wait_for_ssi

  ldr r1, [r0, #0x60]

  // Disable SSI
  movs r1, #0
  str r1, [r0, #0x08]

ssi_config:
  // Setup SPI_CTRL0
  ldr r1, =(0xA0 << 24 | 8 << 2 | 4 << 11 | 0 << 8 | 2 << 0) // 0xA0 XIP cmd, 8 bit addr len, 4 wait cycles, no instruction, 2c2a trans type
  movs r2, #0xF4
  str r1, [r0, r2]

  // Enable SSI
  movs r1, #1
  str r1, [r0, #0x08]

exit_boot2:
  ldr r0, =APP_BASE
  ldr r1, =(PPB_BASE + VTOR)
  str r0, [r1]

  ldmia r0, {r0, r1}
  msr msp, r0
  bx r1
  // unreachable

dead:
    wfi
    b dead

// wait until SSI ready helper
wait_for_ssi:
  push {r1, r2, lr}

1:
  ldr r1, [r0, #0x28] // read SSI status register
  movs r2, #0b100 // TFE bit
  tst r1, r2
  beq 1b
  movs r2, #0b1 // BUSY bit
  tst r1, r2
  bne 1b

  pop {r1, r2, pc}

.ltorg

// Padding to 252 bytes
.space (252 - (. - _stage2_boot))

.word 0x00000000

.end
