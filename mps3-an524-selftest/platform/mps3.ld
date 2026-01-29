/*
 * Linker script for MPS3-AN524 (Cortex-M33)
 * Ensures data is contiguous with code in ROM for proper loading
 */

/* Memory layout */
__ROM_BASE = 0x10000000;
__ROM_SIZE = 0x00200000;  /* 2MB */

__RAM_BASE = 0x20000000;
__RAM_SIZE = 0x00020000;  /* 128KB */

MEMORY
{
  FLASH (rx)  : ORIGIN = __ROM_BASE, LENGTH = __ROM_SIZE
  RAM   (rwx) : ORIGIN = __RAM_BASE, LENGTH = __RAM_SIZE
}

ENTRY(Reset_Handler)

/* Single PHDRS entry to create single LOAD segment */
PHDRS
{
  rom PT_LOAD;
}

SECTIONS
{
  /* Code section */
  ER_IROM1 : ALIGN(4)
  {
    KEEP(*(.vectors))
    *(.text*)
    *(.rodata*)
    KEEP(*(.init))
    KEEP(*(.fini))
    *(.eh_frame*)
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    __exidx_start = .;
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    __exidx_end = .;
    . = ALIGN(4);
  } > FLASH :rom

  __etext = .;

  /* Data section - VMA in RAM, LMA contiguous in FLASH */
  RW_IRAM1 : AT(__etext) ALIGN(4)
  {
    __data_start__ = .;
    *(.data*)
    . = ALIGN(4);
    __data_end__ = .;
  } > RAM :rom

  /* BSS section - no load, just reserve space */
  .bss (NOLOAD) :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
  } > RAM

  .heap (NOLOAD) :
  {
    . = ALIGN(8);
    __end__ = .;
    PROVIDE(end = .);
    *(.heap*)
    . = ALIGN(8);
    __HeapLimit = .;
  } > RAM

  .stack (NOLOAD) :
  {
    . = ALIGN(8);
    *(.stack*)
    . = ALIGN(8);
  } > RAM
}
