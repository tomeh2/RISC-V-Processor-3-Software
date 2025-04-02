#ifndef __TIMES_H_
#define __TIMES_H_

#define HZ 1000

typedef int clock_t;

struct tms
{
    clock_t tms_utime;
    clock_t tms_stime;
    clock_t tms_cutime;
    clock_t tms_cstime;
};

clock_t times(struct tms* tm);

#endif