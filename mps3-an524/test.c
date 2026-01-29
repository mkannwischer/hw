/*
 * Test for MPS3-AN524 (Cortex-M33)
 */

#include <stdio.h>
#include "CMSDK_IoT.h"
#include "SMM_MPS3.h"
#include "uart_stdout.h"
#include "semihosting.h"

extern void SystemCoreClockUpdate(unsigned int clock);

int main(void)
{
    /* Read actual clock from FPGA and update SystemCoreClock */
    unsigned int core_clock = MPS3_SCC->CFG_ACLK;
    if (core_clock != 0)
        SystemCoreClockUpdate(core_clock);

    /* Initialize UART */
    UartStdOutInit();

    puts("MPS3-AN524 Test");
    puts("Hello from GCC build!");

    /* Exit QEMU gracefully */
    semihosting_exit();

    return 0;
}
