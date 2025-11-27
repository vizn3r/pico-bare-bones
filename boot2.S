.syntax unified
.cpu cortex-m0plus
.thumb

.section .boot2, "ax"

#define SPI_FAST

#define SSI_BASE      0x18000000
#define PPB_BASE      0xE0000000
#define APP_BASE      0x10000100
#define VTOR          0xED08

// SSI_CTRL0 values
#ifdef SPI_FAST
#define SPI_FRF (0x2 << 21) // 0x2 > QUAD SPI
#else
#define SPI_FRF (0x0 << 21)
#endif
#define DFS_32 (31 << 16)
#define TMOD (0x3 << 8)

#define SSI_CTRL0 (TMOD | DFS_32 | SPI_FRF)

// SSI_SPI_CTRL0 values
#ifdef SPI_FAST
#define XIP_CMD (0xEB << 24) // for QSPI
#define TRANS_TYPE (0x1 << 0) // for QSPI
#else
#define XIP_CMD (0x03 << 24)
#define TRANS_TYPE (0x0 << 0)
#endif
#define WAIT_CYCLES (4 << 11)
#define INST_L (0x2 << 8)
#define ADDR_L (6 << 2)

#define SSI_SPI_CTRL0 (TRANS_TYPE | ADDR_L | INST_L | WAIT_CYCLES | XIP_CMD)

.global _stage2_boot
.type _stage2_boot,%function
.thumb_func
_stage2_boot:
  bl ssi_config

  ldr r0, =APP_BASE
  ldr r1, =(PPB_BASE + VTOR)
  str r0, [r1]

  ldmia r0, {r0, r1}
  msr msp, r0
  bx r1

ssi_config:

  // Disable SSI
  ldr r0, =SSI_BASE
  movs r1, #0
  str r1, [r0, #0x08]

  // Setup BAUD
  movs r1, #4
  str r1, [r0, #0x14]

  // Setup CTRL0
  ldr r1, =SSI_CTRL0
  str r1, [r0, #0]

  // Setup SPI_CTRL0
  ldr r1, =SSI_SPI_CTRL0
  movs r2, #0xF4
  str r1, [r0, r2]

  // Enable SSI
  movs r1, #1
  str r1, [r0, #0x08]

  bx lr

dead:
    wfi
    b dead

.ltorg

// Padding to 252 bytes
.space (252 - (. - _stage2_boot))

.word 0x00000000

.end
