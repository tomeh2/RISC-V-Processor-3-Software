#include <string.h>
#include <stdio.h>

#define MAX_SUBPROGRAMS 8

#define ARG_STR_MAX_LEN 128
#define ARGV_MAX_LEN 8

struct subroutine
{
    const char* key;
    char arg_str[ARG_STR_MAX_LEN];
    char* argv[8];
    unsigned int argc;
    void (*subroutine)(char** argv, unsigned int argc);
};

static unsigned int table_used_elements = 0;
static struct subroutine table[MAX_SUBPROGRAMS];

void temp_exec_init()
{
    table_used_elements = 0;
}

void temp_register_subroutine(const char* name, void (*subroutine)(char** argv, unsigned int argc))
{
    if (!name || !subroutine || table_used_elements >= MAX_SUBPROGRAMS)
        return;

    table[table_used_elements].key = name;
    table[table_used_elements].subroutine = subroutine;
    table_used_elements++;
}
extern unsigned int history_size;
int exec(const char* name, const char** argv, unsigned int argc)
{
    if (!name)
        return -1;

    struct subroutine* n = NULL;
    for (unsigned int i = 0; i < MAX_SUBPROGRAMS; i++)
    {
        if (!strcmp(name, table[i].key))
            n = &table[i];
    }

    // Subroutine not found
    if (!n)
        return -1;

    // Copy args into subroutine's local buffer
    char* local_argbuf = n->arg_str;
    for (unsigned int i = 0; i < argc; i++)
    {
        n->argv[i] = local_argbuf;
        unsigned int arg_len = strlen(argv[i]);
        memcpy(local_argbuf, argv[i], arg_len);
        local_argbuf += arg_len;
        *local_argbuf++ = '\0';
    }
    n->argc = argc;
    n->subroutine(n->argv, n->argc);

    return 0;
}