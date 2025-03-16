#ifndef __DRIVER_MM_H_
#define __DRIVER_MM_H_

#include <stdint.h>
#include <stddef.h>

struct driver_mm
{
	volatile int32_t* base_addr;
	size_t mem_size;
};

#endif
