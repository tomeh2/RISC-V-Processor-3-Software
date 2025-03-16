#ifndef __GPIO_H_
#define __GPIO_H_

#include <drivers/driver_mm.h>

#define GPIO_DIRECTION_IN 0
#define GPIO_DIRECTION_OUT 1

#define GPIO_OUTPUT_LOW 0
#define GPIO_OUTPUT_HIGH 1

struct gpio_driver;

struct gpio_driver_ops
{
    void (*init)(struct gpio_driver* driver);
    void (*set_direction)(struct gpio_driver* driver, unsigned int offset, int value);
    unsigned int (*get_direction)(struct gpio_driver* driver, unsigned int offset);
    void (*set)(struct gpio_driver* driver, unsigned int offset, int value);
    unsigned int (*get)(struct gpio_driver* driver, unsigned int offset);
    void (*set_multiple)(struct gpio_driver* driver, unsigned int mask, int value);
    unsigned int (*get_multiple)(struct gpio_driver* driver, unsigned int mask);
};

struct gpio_driver
{
    struct driver_mm mm;
    struct gpio_driver_ops* ops;
};

#endif
