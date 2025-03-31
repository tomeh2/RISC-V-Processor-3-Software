#include <time.h>
#include <syscall.h>

clock_t clock(void)
{
    clock_t time = 0;
    sys_gettime(&time);
    return time;
}

time_t time(time_t* timer)
{
    return (time_t) -1;
}