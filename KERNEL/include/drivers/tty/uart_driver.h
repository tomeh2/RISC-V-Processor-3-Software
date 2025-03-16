#ifndef __UART_DRIVER_H_
#define __UART_DRIVER_H_

#include <drivers/driver_mm.h>

struct uart_driver;

struct uart_parameters
{
    uint32_t baudrate;
};

struct uart_driver_ops
{
    void (*init)(struct uart_driver* driver);
	void (*deinit)(struct uart_driver* driver);
    char (*poll_get_char)(struct uart_driver* driver);
    void (*poll_put_char)(struct uart_driver* driver, char ch);
};

struct uart_driver
{
	struct driver_mm mm;
    struct uart_parameters params;
	struct uart_driver_ops* ops;
};

#endif
