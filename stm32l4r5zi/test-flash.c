#include <stdlib.h>
#include <stdio.h>
#include "hal.h"

#include "hal-flash.h"


static int test(void){
    unsigned char d[100];
    char str[100];
    for(size_t i=0;i<sizeof d;i++){
        d[i] = i;
    }

    write_to_flash(d, sizeof d);

    const unsigned char *dflash = get_flash_addr();


    sprintf(str, "addr: %p", dflash);
    hal_send_str(str);

    for(size_t i=0;i<sizeof d; i++){
        if(dflash[i] != d[i]){
            sprintf(str, "Error %u: %x != %x", i, dflash[i], d[i]);
            hal_send_str(str);
            return -1;
        }
    }
    return 0;
}

static void bench(void){
    uint64_t t0, t1;
    unsigned char str[100];
    // 512 KiB
    unsigned char d[1024*512];
    for(size_t i=0;i<sizeof d;i++){
        d[i] = (unsigned char) i;
    }

    for(size_t size=1;size <= sizeof d; size <<= 1){
        t0 = hal_get_time();
        write_to_flash(d, size);
        t1 = hal_get_time();

        sprintf(str, "wrote %lu bytes in %llu cycles (%.2f cycles/byte)", size, t1-t0, (double)(t1-t0)/size);
        hal_send_str(str);
    }

}


int main(void){
  hal_setup(CLOCK_BENCHMARK);
  hal_send_str("======================");
  hal_send_str("flash test\n");
  int rc = test();
  if(!rc) hal_send_str("ALL GOOD!");
  bench();
  hal_send_str("#");
  while(1);
  return 0;
}
