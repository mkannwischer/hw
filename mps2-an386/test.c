#include <stdlib.h>
#include "hal.h"

int main(void){
  hal_setup(CLOCK_BENCHMARK);
  hal_send_str("Hello\n");

  return 0;
}
