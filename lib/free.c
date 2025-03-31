#include <syscall.h>
#include <stddef.h>

void free(void* ptr)
{
    if (ptr)
        sys_free(ptr);
}