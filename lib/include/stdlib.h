#ifndef __STDLIB_H_
#define __STDLIB_H_

#include <stddef.h>

int atoi(const char* str);
void* malloc(size_t size);
void free(void* ptr);

#endif