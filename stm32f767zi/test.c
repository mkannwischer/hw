#include <stdlib.h>
#include <stdio.h>
#include "hal.h"

int main(void)
{
  hal_setup(CLOCK_BENCHMARK);
  hal_send_str("test\n");

  char str[100];

  uint64_t t0, t1;

  for (int k = 1; k < 30; k++)
  {
    t0 = hal_get_time();
    for (int i = 0; i < (1 << k); i++)
    {
      asm("nop");
    }
    t1 = hal_get_time();
    sprintf(str, "t=%llu", t1 - t0);
    hal_send_str(str);
  }

  while (1)
    ;
  return 0;
}
