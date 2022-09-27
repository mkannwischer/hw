#ifndef HAL_FLASH_H
#define HAL_FLASH_H

#include <stddef.h>

int write_to_flash(const unsigned char *data, size_t len);
const unsigned char *get_flash_addr(void);

#endif