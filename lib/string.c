#include "string.h"

#include <stdint.h>

int strcmp(const char* str1, const char* str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

int strncmp(const char* str1, const char* str2, size_t num)
{
	while (num && *str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
		num--;
	}

	if (!num)
		return 0;
	else
		return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

unsigned int strlen(const char* str)
{
	unsigned int len = 0;
	while (*str++)
		len++;
	return len;
}

void strrev(char* str, unsigned int strlen)
{
	if (strlen < 2)
		return;

	unsigned int l = 0;
	unsigned int r = strlen - 1;
	char t;

	while (l < r)
	{
		t = str[l];
		str[l] = str[r];
		str[r] = t;

		l++;
		r--;
	}
}

char* strtok_state_str = NULL;
char* strtok(char* str, const char* delimeters)
{
        if (str)
                strtok_state_str = str;
        else
                if (!strtok_state_str)
                        return NULL;

        char* token_start = NULL;
        int is_delimeter = 0;
        while (*strtok_state_str)
        {
                const char* delimeters_ptr = delimeters;
                while (*delimeters_ptr)
                {
                        if (*strtok_state_str == *delimeters_ptr)
                        {
                                is_delimeter = 1;
                                break;
                        }
                        delimeters_ptr++;
                }

                if (is_delimeter)
                {
                        *strtok_state_str = '\0';
                        is_delimeter = 0;
                        if (token_start)
                        {
                                strtok_state_str++;
                                return token_start;
                        }
                }
                else
                        if (!token_start)
                                token_start = strtok_state_str;
                strtok_state_str++;
        }

        // Found NULL character in string. Finish up.
        strtok_state_str = NULL;
        return token_start;
}

void* memcpy(void* dst, const void* src, size_t len)
{
	uint8_t* p_dst = (uint8_t*) dst;
	const uint8_t* p_src = (const uint8_t*) src;

	for (size_t i = 0; i < len; i++)
		*p_dst++ = *p_src++;

	return dst;
}

void* memset(void* ptr, int val, size_t len)
{
	unsigned char* cptr = (unsigned char*) ptr;
	for (size_t i = 0; i < len; i++)
		*cptr++ = (unsigned char) val;
	return ptr;
}