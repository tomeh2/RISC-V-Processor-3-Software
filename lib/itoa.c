#include <string.h>

char* itoa(int val, char* str, int base)
{
	unsigned int str_len = 0;
	if (val < 0)
	{
		*str++ = '-';
	}
	
	if (!val)
	{
		*str++ = '0';
		str_len++;
	}
	else
	{
		while (val)
		{
			unsigned int digit = val % base;
			digit < 10 ? (*str++ = digit + 48) : (*str++ = digit + 55);
			val /= base;
			str_len++;
		}
	}

	*str = '\0';
	str -= str_len;

	strrev(str, str_len);
	return str;
}