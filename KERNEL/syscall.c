#include <syscall.h>
#include <console.h>

// Everything goes to console for now
extern struct console uart_console;

void sys_write(const char* buf, unsigned int len)
{
    uart_console.ops->write(&uart_console, buf, len);
}