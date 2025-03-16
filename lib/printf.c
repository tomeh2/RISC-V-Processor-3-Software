#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include <syscall.h>

#include <console.h>

int putc(const char ch)
{
	sys_write(&ch, 1);
	return 0;
}

int print(const char* restrict str)
{
	unsigned int str_len = strlen(str);
	sys_write(str, str_len);
	return 0;
}

int printf(const char* restrict format, ...)
{
	va_list params;
	va_start(params, format);
	char temp_buf[16];

	while (*format != '\0')
	{
		if (*format != '%')
		{
			putc(*format);
			format++;
			continue;
		}
		format++;
		switch (*format)
		{
			case 'd':
			{
				int arg = va_arg(params, int);
				itoa(arg, temp_buf, 10);
				print(temp_buf);
				break;
			}
			case 'c':
			{
				char arg = (char) va_arg(params, int);
				putc(arg);
				break;
			}
			case 's':
			{
				const char* arg = va_arg(params, const char*);
				print(arg);
				break;
			}
			case 'x':
			{
				int arg = va_arg(params, int);
				itoa(arg, temp_buf, 16);
				print(temp_buf);
				break;
			}
			case 'o':
			{
				int arg = va_arg(params, int);
				itoa(arg, temp_buf, 8);
				print(temp_buf);
				break;
			}
		}
		format++;
	}
	va_end(params);
	return 0;
}
