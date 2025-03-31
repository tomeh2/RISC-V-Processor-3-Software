#ifndef __TIME_H_
#define __TIME_H_

#define CLOCKS_PER_SEC 1000000

typedef unsigned int time_t;
typedef unsigned int clock_t;

struct tm
{
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

struct timespec
{
    time_t tv_sec;
    long tv_nsec;
};

clock_t clock(void);
time_t time(time_t* timer);

#endif