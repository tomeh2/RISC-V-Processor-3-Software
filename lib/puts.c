#include <string.h>

#include <syscall.h>

int puts(const char* restrict str)
{
	unsigned int str_len = strlen(str);
	sys_write(str, str_len);
	return 0;
}