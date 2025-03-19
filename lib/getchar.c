#include <syscall.h>

int getchar()
{
    char ch;
    sys_read(&ch, 1);
    return ch;
}