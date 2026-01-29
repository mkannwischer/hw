/*
 * Semihosting support for QEMU exit
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>

#define REPORT_EXCEPTION 0x18
#define ApplicationExit  0x20026

/* Do a semihosting system call */
static uint32_t semihosting_syscall(uint32_t nr, const uint32_t arg)
{
    __asm__ volatile (
        "mov r0, %[nr]\n"
        "mov r1, %[arg]\n"
        "bkpt 0xAB\n"
        "mov %[nr], r0\n"
        : [nr] "+r" (nr)
        : [arg] "r" (arg)
        : "r0", "r1"
    );
    return nr;
}

/* Call this to exit QEMU gracefully */
void semihosting_exit(void)
{
    semihosting_syscall(REPORT_EXCEPTION, ApplicationExit);
}
