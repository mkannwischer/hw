#include "ARMCM85.h"
#include "system_ARMCM85.h"
#include "uart.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "randombytes.h"

// static volatile unsigned long long overflowcnt = 0;
// void SysTick_Handler(void)
// {
//    ++overflowcnt;
// }

// static uint64_t hal_get_time(){
//   while (1) {
//     unsigned long long before = overflowcnt;
//     unsigned long long result = (before + 1) * 16777216llu - SysTick->VAL;
//     if (overflowcnt == before) {
//       return result;
//     }
//   }
// }

int main(void)
{
  // uint64_t t0, t1;
  // char str[100];
  // SysTick_Config(0xFFFFFFu);
  // uart_putc("bla");
  puts("Hello from Cortex-M85!\n");
  printf("test2");


  // puts(".............");

  // t0 = hal_get_time();
  // for(int i=0;i<100000;i++){
  //   asm("nop");
  // }
  // t1 = hal_get_time();

  // sprintf(str, "%llu cycles", t1-t0);
  // puts(str);

  return 0;
}