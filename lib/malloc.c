#include <syscall.h>
#include <stddef.h>

void* malloc(size_t size)
{
    if (size)
        return sys_alloc(size);
    return NULL;
}