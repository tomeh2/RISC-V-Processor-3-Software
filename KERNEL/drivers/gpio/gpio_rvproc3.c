#include <drivers/gpio/gpio_rvproc3.h>

#define GPIO_IN_REG 0
#define GPIO_OUT_REG 1

void gpio_rvproc3_init()
{
}

void gpio_rvproc3_set_direction(struct gpio_driver* driver, unsigned int offset, int value)
{
}

unsigned int gpio_rvproc3_get_direction(struct gpio_driver* driver, unsigned int offset)
{
	return -1;
}

void gpio_rvproc3_set(struct gpio_driver* driver, unsigned int offset, int value)
{
	if (value)
		*(driver->mm.base_addr + GPIO_OUT_REG) |= 1 << offset;
	else
		*(driver->mm.base_addr + GPIO_OUT_REG) &= ~(1 << offset);
}

unsigned int gpio_rvproc3_get(struct gpio_driver* driver, unsigned int offset)
{
	return (*(driver->mm.base_addr + GPIO_IN_REG) >> offset) & 1;
}

void gpio_rvproc3_set_multiple(struct gpio_driver* driver, unsigned int mask, int value)
{
	int old_val = *(driver->mm.base_addr + GPIO_OUT_REG);
	*(driver->mm.base_addr + GPIO_OUT_REG) = (old_val & ~mask) | (value & mask);
}

unsigned int gpio_rvproc3_get_multiple(struct gpio_driver* driver, unsigned int mask)
{
	return *(driver->mm.base_addr + GPIO_IN_REG) & mask;
}

struct gpio_driver_ops gpio_rvproc3_ops =
{
	.init = gpio_rvproc3_init,
	.set_direction = gpio_rvproc3_set_direction,
	.get_direction = gpio_rvproc3_get_direction,
	.set = gpio_rvproc3_set,
	.get = gpio_rvproc3_get,
	.set_multiple = gpio_rvproc3_set_multiple,
	.get_multiple = gpio_rvproc3_get_multiple
};