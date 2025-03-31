#include <syscall.h>
#include <sysclk.h>
#include <arch/riscv/csr.h>
#include <drivers/tty/uart_rvproc3.h>
#include <mem/memory.h>

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

#define TIME_DIV (SYSCLK_HZ / 1000000)

void sys_gettime(unsigned int* t)
{
    unsigned int temp;
    CSR_READ(temp, CSR_CYCLE);
    *t = temp / TIME_DIV;
}

void* sys_alloc(size_t size)
{
    return mm_alloc(size);
}

void sys_free(void* ptr)
{
    mm_free(ptr);
}