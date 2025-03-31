#ifndef __STRING_H_
#define __STRING_H_

#include <stddef.h>

int strcmp(const char* str1, const char* str2);
int strncmp(const char* str1, const char* str2, size_t num);
char* strcpy(char* dst, const char* src);
unsigned int strlen(const char* str);
void strrev(char* str, unsigned int strlen);
char* strtok(char* str, const char* delimeters);
void* memcpy(void* dst, const void* src, size_t len);
void* memset(void* ptr, int val, size_t len);

#endif
