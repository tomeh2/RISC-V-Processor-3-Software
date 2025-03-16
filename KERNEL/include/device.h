#ifndef __DEVICE_H_
#define __DEVICE_H_

#include "stdint.h"

struct driver;

struct driver_mm
{
	volatile uint32_t* base_addr;
	uint32_t mem_size;
};

struct driver_ops
{	
	int8_t (*init)(struct driver* drv);
	int8_t (*read)(struct driver* drv, uint8_t dev_addr, uint8_t* buf, size_t len);
	int8_t (*write)(struct driver* drv, uint8_t dev_addr, uint8_t* buf, size_t len);
	int8_t (*ioctl)(struct driver* drv, int32_t op);
};

struct driver
{
	struct driver_mm dev_mm;
	struct driver_ops* ops;
};

#endif
