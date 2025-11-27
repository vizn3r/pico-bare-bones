ENTRY(_start)

MEMORY {
  BOOT2(rx) : ORIGIN = 0x10000000, LENGTH = 256
  FLASH(rx) : ORIGIN = 0x10000100, LENGTH = 2M - 256
  RAM(rwx)  : ORIGIN = 0x20000000, LENGTH = 264K
}

SECTIONS {
  .boot2 : {
    KEEP(*(.boot2))
  } > BOOT2

  .text : {
    KEEP(*(.vectors))
    *(.text._start)
    *(.text)
    *(.text*)
  } > FLASH

  .rodata : {
    *(.rodata)
    *(.rodata*)
  } > FLASH

  .data : {
    __data_start = .;
    *(.data)
    *(.data*)
    __data_end = .;
  } > RAM AT > FLASH

  __data_load = LOADADDR(.data);

  .bss : {
    __bss_start = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    __bss_end = .;
  } > RAM

  _stack_top = ORIGIN(RAM) + LENGTH(RAM);
}
