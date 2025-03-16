#ifndef __I2C_H_
#define __I2C_H_

#include <stdint.h>
#include <stddef.h>

#include <drivers/driver_mm.h>

struct i2c_bus_driver;

struct i2c_parameters
{
    uint16_t i2c_freq_khz;
};

struct i2c_bus_driver_ops
{
	int8_t (*init)(struct i2c_bus_driver* bus_driver);
	int8_t (*read)(struct i2c_bus_driver* bus_driver, uint8_t dev_addr, uint8_t* buf, size_t size);
	int8_t (*write)(struct i2c_bus_driver* bus_driver, uint8_t dev_addr, uint8_t* buf, size_t size);
	int8_t (*ioctl)(struct i2c_bus_driver* bus_driver, int32_t op);
};

struct i2c_bus_driver
{
	struct driver_mm mm;
    struct i2c_parameters params;
	struct i2c_bus_driver_ops* ops;
};

#endif
