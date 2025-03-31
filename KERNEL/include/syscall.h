#ifndef __SYSCALL_H_
#define __SYSCALL_H_

#include <stddef.h>

void sys_write(const char* buf, unsigned int len);
void sys_read(char* buf, unsigned int len);
void sys_gettime(unsigned int* t);
void* sys_alloc(size_t size);
void sys_free(void* ptr);

#endif