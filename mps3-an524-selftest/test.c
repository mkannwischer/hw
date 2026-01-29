/*
 * Minimal test for MPS3-AN524 - copied from AN524 selftest main.c
 * Uses exact same initialization sequence as working AN524 selftest
 */

#include <stdio.h>
#include "SMM_MPS3.h"
#include "uart_stdout.h"
#include "system_CMSDK_IoT.h"

int main(void)
{
    /* EXACT initialization sequence from AN524 selftest main.c */
    unsigned int core_clock = MPS3_SCC->CFG_ACLK;
    if (core_clock != 0)
        SystemCoreClockUpdate(core_clock);

    /* UART init - same as AN524 selftest */
    UartStdOutInit();

    /* Clear pending IRQs - same as AN524 selftest */
    NVIC_ClearAllPendingIRQ();

    /* Use printf like AN524 selftest does */
    printf("\n\nMPS3-AN524 Test\n");
    printf("Hello from GCC build!\n");

    /* Loop forever */
    while(1) {
        MPS3_FPGAIO->LED ^= 0x01;
        for (volatile int i = 0; i < 500000; i++);
    }

    return 0;
}
