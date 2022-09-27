
#include "hal-flash.h"
#include <string.h>
#include <libopencm3/stm32/flash.h>

#define FLASH_PAGE_SIZE  0x1000
// starts at offset 1 MiB
// flash starts at 0x08000000
// our data starts at 0x08100000
#define FLASH_PAGE_START_IDX  256
// 1 MiB
#define FLASH_N_PAGES      256
#define FLASH_SIZE    ((FLASH_N_PAGES)*(FLASH_PAGE_SIZE))


__attribute__((__section__(".flash_data"))) const unsigned char flash_data[FLASH_SIZE];


static uint64_t byte_to_uint64_le(const unsigned char *d, size_t len){
    uint64_t v = 0;
    if(len > 0) v |= ((uint64_t)d[0]) << (8*0);
    if(len > 1) v |= ((uint64_t)d[1]) << (8*1);
    if(len > 2) v |= ((uint64_t)d[2]) << (8*2);
    if(len > 3) v |= ((uint64_t)d[3]) << (8*3);
    if(len > 4) v |= ((uint64_t)d[4]) << (8*4);
    if(len > 5) v |= ((uint64_t)d[5]) << (8*5);
    if(len > 6) v |= ((uint64_t)d[6]) << (8*6);
    if(len > 7) v |= ((uint64_t)d[7]) << (8*7);
    return v;
}

int write_to_flash(const unsigned char *data, size_t len){
    if(len > FLASH_SIZE) return -1;

    size_t first_page = FLASH_PAGE_START_IDX;
    size_t last_page  = first_page + (len + FLASH_PAGE_SIZE - 1) / FLASH_PAGE_SIZE;


    // unlock flash
    flash_unlock();

    // erase flash
    for(size_t i=first_page;i<last_page;i++) flash_erase_page(i);

    // write to flash
    flash_program(flash_data, data, len);
    if(len % 8){
        flash_program_double_word(flash_data + len - (len % 8), byte_to_uint64_le(data + len - (len % 8), len % 8));
    }

    // lock flash
    flash_lock();

    return 0;
}

const unsigned char *get_flash_addr(void){
    return flash_data;
}