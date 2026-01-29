/*
 * Startup file for CMSDK_IoT Device (GNU assembler version)
 * Converted from Arm Compiler armasm syntax
 * Copyright (c) 2011 - 2013 ARM LIMITED
 */

    .syntax unified
    .arch armv8-m.main
    .thumb

/* Stack and Heap sizes - matching original AN524 selftest */
    .equ Stack_Size, 0x00001000     /* 4KB stack */
    .equ Heap_Size,  0x00001000     /* 4KB heap (reduced from 64KB) */

/* Stack section */
    .section .stack, "w"
    .align 3
Stack_Mem:
    .space Stack_Size
    .globl __initial_sp
__initial_sp:

/* Heap section */
    .section .heap, "w"
    .align 3
    .globl __heap_base
__heap_base:
Heap_Mem:
    .space Heap_Size
    .globl __heap_limit
__heap_limit:

/* Vector Table */
    .section .vectors, "a"
    .align 2
    .globl __Vectors
    .globl __Vectors_End
    .globl __Vectors_Size

__Vectors:
    .word   __initial_sp              /* Top of Stack */
    .word   Reset_Handler             /* Reset Handler */
    .word   NMI_Handler               /* NMI Handler */
    .word   HardFault_Handler         /* Hard Fault Handler */
    .word   MemManage_Handler         /* MPU Fault Handler */
    .word   BusFault_Handler          /* Bus Fault Handler */
    .word   UsageFault_Handler        /* Usage Fault Handler */
    .word   SecureFault_Handler       /* Secure Fault Handler */
    .word   0                         /* Reserved */
    .word   0                         /* Reserved */
    .word   0                         /* Reserved */
    .word   SVC_Handler               /* SVCall Handler */
    .word   DebugMon_Handler          /* Debug Monitor Handler */
    .word   0                         /* Reserved */
    .word   PendSV_Handler            /* PendSV Handler */
    .word   SysTick_Handler           /* SysTick Handler */

    /* Core IoT Interrupts */
    .word   NONSEC_WATCHDOG_RESET_Handler  /* 0 */
    .word   NONSEC_WATCHDOG_Handler        /* 1 */
    .word   S32K_TIMER_Handler             /* 2 */
    .word   TIMER0_Handler                 /* 3 */
    .word   TIMER1_Handler                 /* 4 */
    .word   DUALTIMER_Handler              /* 5 */
    .word   0                              /* 6 Reserved */
    .word   0                              /* 7 Reserved */
    .word   0                              /* 8 Reserved */
    .word   MPC_Handler                    /* 9 */
    .word   PPC_Handler                    /* 10 */
    .word   MSC_Handler                    /* 11 */
    .word   BRIDGE_ERROR_Handler           /* 12 */
    .word   0                              /* 13 Reserved */
    .word   0                              /* 14 Reserved */
    .word   0                              /* 15 Reserved */
    .word   0                              /* 16 Reserved */
    .word   0                              /* 17 Reserved */
    .word   0                              /* 18 Reserved */
    .word   0                              /* 19 Reserved */
    .word   0                              /* 20 Reserved */
    .word   0                              /* 21 Reserved */
    .word   0                              /* 22 Reserved */
    .word   0                              /* 23 Reserved */
    .word   0                              /* 24 Reserved */
    .word   0                              /* 25 Reserved */
    .word   0                              /* 26 Reserved */
    .word   0                              /* 27 Reserved */
    .word   0                              /* 28 Reserved */
    .word   0                              /* 29 Reserved */
    .word   0                              /* 30 Reserved */
    .word   0                              /* 31 Reserved */

    /* External Interrupts */
    .word   UARTRX0_Handler           /* 32 */
    .word   UARTTX0_Handler           /* 33 */
    .word   UARTRX1_Handler           /* 34 */
    .word   UARTTX1_Handler           /* 35 */
    .word   UARTRX2_Handler           /* 36 */
    .word   UARTTX2_Handler           /* 37 */
    .word   UARTRX3_Handler           /* 38 */
    .word   UARTTX3_Handler           /* 39 */
    .word   UARTRX4_Handler           /* 40 */
    .word   UARTTX4_Handler           /* 41 */
    .word   UART0_Handler             /* 42 */
    .word   UART1_Handler             /* 43 */
    .word   UART2_Handler             /* 44 */
    .word   UART3_Handler             /* 45 */
    .word   UART4_Handler             /* 46 */
    .word   UARTOVF_Handler           /* 47 */
    .word   ETHERNET_Handler          /* 48 */
    .word   I2S_Handler               /* 49 */
    .word   TSC_Handler               /* 50 */
    .word   USB_Handler               /* 51 */
    .word   SPI2_Handler              /* 52 */
    .word   SPI3_Handler              /* 53 */
    .word   SPI4_Handler              /* 54 */
    .word   HDMI_I2S_Handler          /* 55 */
    .word   0                         /* 56 Reserved */
    .word   0                         /* 57 Reserved */
    .word   0                         /* 58 Reserved */
    .word   0                         /* 59 Reserved */
    .word   0                         /* 60 Reserved */
    .word   0                         /* 61 Reserved */
    .word   0                         /* 62 Reserved */
    .word   0                         /* 63 Reserved */
    .word   0                         /* 64 Reserved */
    .word   0                         /* 65 Reserved */
    .word   0                         /* 66 Reserved */
    .word   0                         /* 67 Reserved */
    .word   GPIO0_Handler             /* 68 */
    .word   GPIO1_Handler             /* 69 */
    .word   GPIO2_Handler             /* 70 */
    .word   GPIO3_Handler             /* 71 */
    .word   GPIO0_0_Handler           /* 72 */
    .word   GPIO0_1_Handler           /* 73 */
    .word   GPIO0_2_Handler           /* 74 */
    .word   GPIO0_3_Handler           /* 75 */
    .word   GPIO0_4_Handler           /* 76 */
    .word   GPIO0_5_Handler           /* 77 */
    .word   GPIO0_6_Handler           /* 78 */
    .word   GPIO0_7_Handler           /* 79 */
    .word   GPIO0_8_Handler           /* 80 */
    .word   GPIO0_9_Handler           /* 81 */
    .word   GPIO0_10_Handler          /* 82 */
    .word   GPIO0_11_Handler          /* 83 */
    .word   GPIO0_12_Handler          /* 84 */
    .word   GPIO0_13_Handler          /* 85 */
    .word   GPIO0_14_Handler          /* 86 */
    .word   GPIO0_15_Handler          /* 87 */
    .word   GPIO1_0_Handler           /* 88 */
    .word   GPIO1_1_Handler           /* 89 */
    .word   GPIO1_2_Handler           /* 90 */
    .word   GPIO1_3_Handler           /* 91 */
    .word   GPIO1_4_Handler           /* 92 */
    .word   GPIO1_5_Handler           /* 93 */
    .word   GPIO1_6_Handler           /* 94 */
    .word   GPIO1_7_Handler           /* 95 */
    .word   GPIO1_8_Handler           /* 96 */
    .word   GPIO1_9_Handler           /* 97 */
    .word   GPIO1_10_Handler          /* 98 */
    .word   GPIO1_11_Handler          /* 99 */
    .word   GPIO1_12_Handler          /* 100 */
    .word   GPIO1_13_Handler          /* 101 */
    .word   GPIO1_14_Handler          /* 102 */
    .word   GPIO1_15_Handler          /* 103 */
    .word   GPIO2_0_Handler           /* 104 */
    .word   GPIO2_1_Handler           /* 105 */
    .word   GPIO2_2_Handler           /* 106 */
    .word   GPIO2_3_Handler           /* 107 */
    .word   GPIO2_4_Handler           /* 108 */
    .word   GPIO2_5_Handler           /* 109 */
    .word   GPIO2_6_Handler           /* 110 */
    .word   GPIO2_7_Handler           /* 111 */
    .word   GPIO2_8_Handler           /* 112 */
    .word   GPIO2_9_Handler           /* 113 */
    .word   GPIO2_10_Handler          /* 114 */
    .word   GPIO2_11_Handler          /* 115 */
    .word   GPIO2_12_Handler          /* 116 */
    .word   GPIO2_13_Handler          /* 117 */
    .word   GPIO2_14_Handler          /* 118 */
    .word   GPIO2_15_Handler          /* 119 */
    .word   GPIO3_0_Handler           /* 120 */
    .word   GPIO3_1_Handler           /* 121 */
    .word   GPIO3_2_Handler           /* 122 */
    .word   GPIO3_3_Handler           /* 123 */
    .word   UARTRX5_Handler           /* 124 */
    .word   UARTTX5_Handler           /* 125 */
    .word   UART5_Handler             /* 126 */
    .word   HDLCD_Handler             /* 127 */
__Vectors_End:

    .equ __Vectors_Size, __Vectors_End - __Vectors

/* Reset Handler */
    .section .text
    .align 2
    .thumb
    .globl Reset_Handler
    .type Reset_Handler, %function
Reset_Handler:
    /* Call SystemInit */
    ldr     r0, =SystemInit
    blx     r0

    /* Copy .data from ROM to RAM */
    ldr     r1, =__etext        /* source (ROM) */
    ldr     r2, =__data_start__ /* destination (RAM) */
    ldr     r3, =__data_end__
.L_copy_data:
    cmp     r2, r3
    bge     .L_copy_done
    ldr     r0, [r1], #4
    str     r0, [r2], #4
    b       .L_copy_data
.L_copy_done:

    /* Clear BSS */
    ldr     r1, =__bss_start__
    ldr     r2, =__bss_end__
    movs    r0, #0
.L_clear_bss:
    cmp     r1, r2
    bge     .L_bss_done
    str     r0, [r1], #4
    b       .L_clear_bss
.L_bss_done:

    /* Call main */
    bl      main

    /* If main returns, loop forever */
.L_loop:
    b       .L_loop
    .size Reset_Handler, . - Reset_Handler

/* Exception Handlers */
    .thumb_func
    .weak NMI_Handler
    .type NMI_Handler, %function
NMI_Handler:
    b       .
    .size NMI_Handler, . - NMI_Handler

    .thumb_func
    .weak HardFault_Handler
    .type HardFault_Handler, %function
HardFault_Handler:
    b       .
    .size HardFault_Handler, . - HardFault_Handler

    .thumb_func
    .weak MemManage_Handler
    .type MemManage_Handler, %function
MemManage_Handler:
    b       .
    .size MemManage_Handler, . - MemManage_Handler

    .thumb_func
    .weak BusFault_Handler
    .type BusFault_Handler, %function
BusFault_Handler:
    b       .
    .size BusFault_Handler, . - BusFault_Handler

    .thumb_func
    .weak UsageFault_Handler
    .type UsageFault_Handler, %function
UsageFault_Handler:
    b       .
    .size UsageFault_Handler, . - UsageFault_Handler

    .thumb_func
    .weak SecureFault_Handler
    .type SecureFault_Handler, %function
SecureFault_Handler:
    b       .
    .size SecureFault_Handler, . - SecureFault_Handler

    .thumb_func
    .weak SVC_Handler
    .type SVC_Handler, %function
SVC_Handler:
    b       .
    .size SVC_Handler, . - SVC_Handler

    .thumb_func
    .weak DebugMon_Handler
    .type DebugMon_Handler, %function
DebugMon_Handler:
    b       .
    .size DebugMon_Handler, . - DebugMon_Handler

    .thumb_func
    .weak PendSV_Handler
    .type PendSV_Handler, %function
PendSV_Handler:
    b       .
    .size PendSV_Handler, . - PendSV_Handler

    .thumb_func
    .weak SysTick_Handler
    .type SysTick_Handler, %function
SysTick_Handler:
    b       .
    .size SysTick_Handler, . - SysTick_Handler

/* Default Handler */
    .thumb_func
    .weak Default_Handler
    .type Default_Handler, %function
Default_Handler:
    b       .
    .size Default_Handler, . - Default_Handler

/* Weak aliases for all interrupt handlers */
    .weak   NONSEC_WATCHDOG_RESET_Handler
    .thumb_set NONSEC_WATCHDOG_RESET_Handler, Default_Handler
    .weak   NONSEC_WATCHDOG_Handler
    .thumb_set NONSEC_WATCHDOG_Handler, Default_Handler
    .weak   S32K_TIMER_Handler
    .thumb_set S32K_TIMER_Handler, Default_Handler
    .weak   TIMER0_Handler
    .thumb_set TIMER0_Handler, Default_Handler
    .weak   TIMER1_Handler
    .thumb_set TIMER1_Handler, Default_Handler
    .weak   DUALTIMER_Handler
    .thumb_set DUALTIMER_Handler, Default_Handler
    .weak   MPC_Handler
    .thumb_set MPC_Handler, Default_Handler
    .weak   PPC_Handler
    .thumb_set PPC_Handler, Default_Handler
    .weak   MSC_Handler
    .thumb_set MSC_Handler, Default_Handler
    .weak   BRIDGE_ERROR_Handler
    .thumb_set BRIDGE_ERROR_Handler, Default_Handler
    .weak   UARTRX0_Handler
    .thumb_set UARTRX0_Handler, Default_Handler
    .weak   UARTTX0_Handler
    .thumb_set UARTTX0_Handler, Default_Handler
    .weak   UARTRX1_Handler
    .thumb_set UARTRX1_Handler, Default_Handler
    .weak   UARTTX1_Handler
    .thumb_set UARTTX1_Handler, Default_Handler
    .weak   UARTRX2_Handler
    .thumb_set UARTRX2_Handler, Default_Handler
    .weak   UARTTX2_Handler
    .thumb_set UARTTX2_Handler, Default_Handler
    .weak   UARTRX3_Handler
    .thumb_set UARTRX3_Handler, Default_Handler
    .weak   UARTTX3_Handler
    .thumb_set UARTTX3_Handler, Default_Handler
    .weak   UARTRX4_Handler
    .thumb_set UARTRX4_Handler, Default_Handler
    .weak   UARTTX4_Handler
    .thumb_set UARTTX4_Handler, Default_Handler
    .weak   UART0_Handler
    .thumb_set UART0_Handler, Default_Handler
    .weak   UART1_Handler
    .thumb_set UART1_Handler, Default_Handler
    .weak   UART2_Handler
    .thumb_set UART2_Handler, Default_Handler
    .weak   UART3_Handler
    .thumb_set UART3_Handler, Default_Handler
    .weak   UART4_Handler
    .thumb_set UART4_Handler, Default_Handler
    .weak   UARTOVF_Handler
    .thumb_set UARTOVF_Handler, Default_Handler
    .weak   ETHERNET_Handler
    .thumb_set ETHERNET_Handler, Default_Handler
    .weak   I2S_Handler
    .thumb_set I2S_Handler, Default_Handler
    .weak   TSC_Handler
    .thumb_set TSC_Handler, Default_Handler
    .weak   USB_Handler
    .thumb_set USB_Handler, Default_Handler
    .weak   SPI2_Handler
    .thumb_set SPI2_Handler, Default_Handler
    .weak   SPI3_Handler
    .thumb_set SPI3_Handler, Default_Handler
    .weak   SPI4_Handler
    .thumb_set SPI4_Handler, Default_Handler
    .weak   HDMI_I2S_Handler
    .thumb_set HDMI_I2S_Handler, Default_Handler
    .weak   GPIO0_Handler
    .thumb_set GPIO0_Handler, Default_Handler
    .weak   GPIO1_Handler
    .thumb_set GPIO1_Handler, Default_Handler
    .weak   GPIO2_Handler
    .thumb_set GPIO2_Handler, Default_Handler
    .weak   GPIO3_Handler
    .thumb_set GPIO3_Handler, Default_Handler
    .weak   GPIO0_0_Handler
    .thumb_set GPIO0_0_Handler, Default_Handler
    .weak   GPIO0_1_Handler
    .thumb_set GPIO0_1_Handler, Default_Handler
    .weak   GPIO0_2_Handler
    .thumb_set GPIO0_2_Handler, Default_Handler
    .weak   GPIO0_3_Handler
    .thumb_set GPIO0_3_Handler, Default_Handler
    .weak   GPIO0_4_Handler
    .thumb_set GPIO0_4_Handler, Default_Handler
    .weak   GPIO0_5_Handler
    .thumb_set GPIO0_5_Handler, Default_Handler
    .weak   GPIO0_6_Handler
    .thumb_set GPIO0_6_Handler, Default_Handler
    .weak   GPIO0_7_Handler
    .thumb_set GPIO0_7_Handler, Default_Handler
    .weak   GPIO0_8_Handler
    .thumb_set GPIO0_8_Handler, Default_Handler
    .weak   GPIO0_9_Handler
    .thumb_set GPIO0_9_Handler, Default_Handler
    .weak   GPIO0_10_Handler
    .thumb_set GPIO0_10_Handler, Default_Handler
    .weak   GPIO0_11_Handler
    .thumb_set GPIO0_11_Handler, Default_Handler
    .weak   GPIO0_12_Handler
    .thumb_set GPIO0_12_Handler, Default_Handler
    .weak   GPIO0_13_Handler
    .thumb_set GPIO0_13_Handler, Default_Handler
    .weak   GPIO0_14_Handler
    .thumb_set GPIO0_14_Handler, Default_Handler
    .weak   GPIO0_15_Handler
    .thumb_set GPIO0_15_Handler, Default_Handler
    .weak   GPIO1_0_Handler
    .thumb_set GPIO1_0_Handler, Default_Handler
    .weak   GPIO1_1_Handler
    .thumb_set GPIO1_1_Handler, Default_Handler
    .weak   GPIO1_2_Handler
    .thumb_set GPIO1_2_Handler, Default_Handler
    .weak   GPIO1_3_Handler
    .thumb_set GPIO1_3_Handler, Default_Handler
    .weak   GPIO1_4_Handler
    .thumb_set GPIO1_4_Handler, Default_Handler
    .weak   GPIO1_5_Handler
    .thumb_set GPIO1_5_Handler, Default_Handler
    .weak   GPIO1_6_Handler
    .thumb_set GPIO1_6_Handler, Default_Handler
    .weak   GPIO1_7_Handler
    .thumb_set GPIO1_7_Handler, Default_Handler
    .weak   GPIO1_8_Handler
    .thumb_set GPIO1_8_Handler, Default_Handler
    .weak   GPIO1_9_Handler
    .thumb_set GPIO1_9_Handler, Default_Handler
    .weak   GPIO1_10_Handler
    .thumb_set GPIO1_10_Handler, Default_Handler
    .weak   GPIO1_11_Handler
    .thumb_set GPIO1_11_Handler, Default_Handler
    .weak   GPIO1_12_Handler
    .thumb_set GPIO1_12_Handler, Default_Handler
    .weak   GPIO1_13_Handler
    .thumb_set GPIO1_13_Handler, Default_Handler
    .weak   GPIO1_14_Handler
    .thumb_set GPIO1_14_Handler, Default_Handler
    .weak   GPIO1_15_Handler
    .thumb_set GPIO1_15_Handler, Default_Handler
    .weak   GPIO2_0_Handler
    .thumb_set GPIO2_0_Handler, Default_Handler
    .weak   GPIO2_1_Handler
    .thumb_set GPIO2_1_Handler, Default_Handler
    .weak   GPIO2_2_Handler
    .thumb_set GPIO2_2_Handler, Default_Handler
    .weak   GPIO2_3_Handler
    .thumb_set GPIO2_3_Handler, Default_Handler
    .weak   GPIO2_4_Handler
    .thumb_set GPIO2_4_Handler, Default_Handler
    .weak   GPIO2_5_Handler
    .thumb_set GPIO2_5_Handler, Default_Handler
    .weak   GPIO2_6_Handler
    .thumb_set GPIO2_6_Handler, Default_Handler
    .weak   GPIO2_7_Handler
    .thumb_set GPIO2_7_Handler, Default_Handler
    .weak   GPIO2_8_Handler
    .thumb_set GPIO2_8_Handler, Default_Handler
    .weak   GPIO2_9_Handler
    .thumb_set GPIO2_9_Handler, Default_Handler
    .weak   GPIO2_10_Handler
    .thumb_set GPIO2_10_Handler, Default_Handler
    .weak   GPIO2_11_Handler
    .thumb_set GPIO2_11_Handler, Default_Handler
    .weak   GPIO2_12_Handler
    .thumb_set GPIO2_12_Handler, Default_Handler
    .weak   GPIO2_13_Handler
    .thumb_set GPIO2_13_Handler, Default_Handler
    .weak   GPIO2_14_Handler
    .thumb_set GPIO2_14_Handler, Default_Handler
    .weak   GPIO2_15_Handler
    .thumb_set GPIO2_15_Handler, Default_Handler
    .weak   GPIO3_0_Handler
    .thumb_set GPIO3_0_Handler, Default_Handler
    .weak   GPIO3_1_Handler
    .thumb_set GPIO3_1_Handler, Default_Handler
    .weak   GPIO3_2_Handler
    .thumb_set GPIO3_2_Handler, Default_Handler
    .weak   GPIO3_3_Handler
    .thumb_set GPIO3_3_Handler, Default_Handler
    .weak   UARTRX5_Handler
    .thumb_set UARTRX5_Handler, Default_Handler
    .weak   UARTTX5_Handler
    .thumb_set UARTTX5_Handler, Default_Handler
    .weak   UART5_Handler
    .thumb_set UART5_Handler, Default_Handler
    .weak   HDLCD_Handler
    .thumb_set HDLCD_Handler, Default_Handler

    .end
