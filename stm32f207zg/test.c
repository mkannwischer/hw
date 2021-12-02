#include <stdlib.h>
#include "hal.h"

int main(void){
  hal_setup(CLOCK_BENCHMARK);
  hal_send_str("bla\n");

  while(1);
  return 0;
}
