#include <syscall.h>
#include <drivers/tty/uart_rvproc3.h>

// For now do IO on the default UART driver
extern struct uart_driver tty1_driver;

void sys_write(const char* buf, unsigned int len)
{
    while (len--)
        tty1_driver.ops->poll_put_char(&tty1_driver, *buf++);
}

void sys_read(char* buf, unsigned int len)
{
    while (len--)
        *buf++ = tty1_driver.ops->poll_get_char(&tty1_driver);
}