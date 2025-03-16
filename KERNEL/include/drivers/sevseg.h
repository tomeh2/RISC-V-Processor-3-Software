#ifndef __SEVSEG_H_
#define __SEVSEG_H_

#include <stdint.h>
#include <stddef.h>

void sevseg_init();
void sevseg_write(uint32_t num);

#endif
