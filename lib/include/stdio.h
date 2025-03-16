#ifndef __KSTDIO_H_
#define __KSTDIO_H_

#include <sys/cdefs.h>

#include <console.h>

#ifdef __cplusplus
extern "C" {
#endif

int print(const char* __restrict);
int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);
int putc(const char);

#ifdef __cplusplus
}
#endif

#endif
