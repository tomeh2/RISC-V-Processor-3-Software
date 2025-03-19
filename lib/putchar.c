#include <syscall.h>

int putchar(const char ch)
{
	sys_write(&ch, 1);
	return 0;
}