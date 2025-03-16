#ifndef __SUBROUTINE_H_
#define __SUBROUTINE_H_

#define ARG_STR_MAX_LEN 128
#define ARGV_MAX_LEN 8

struct subroutine
{
    char arg_str[ARG_STR_MAX_LEN];
    char* argv[8];
    unsigned int argc;
    void (*subroutine)(char** argv, unsigned int argc);
};

#endif