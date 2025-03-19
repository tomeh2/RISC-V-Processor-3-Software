#ifndef __KSTDIO_H_
#define __KSTDIO_H_

//#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* __restrict, ...);
int puts(const char*);
int putchar(const char ch);
int getchar();

#ifdef __cplusplus
}
#endif

#endif
