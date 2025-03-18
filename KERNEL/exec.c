#include <string.h>
#include <subroutine.h>

#include <stdio.h>

#define MAX_SUBPROGRAMS 8

struct node
{
    const char* key;
    struct subroutine prog;
};

static unsigned int table_used_elements = 0;
static struct node table[MAX_SUBPROGRAMS];

void temp_exec_init()
{
    table_used_elements = 0;
}

void temp_register_subroutine(const char* name, void (*subroutine)(char** argv, unsigned int argc))
{
    if (!name || !subroutine || table_used_elements >= MAX_SUBPROGRAMS)
        return;

    table[table_used_elements].key = name;
    table[table_used_elements].prog.subroutine = subroutine;
    table_used_elements++;
}

int exec(const char* name, const char** argv, unsigned int argc)
{
    if (!name)
        return -1;

    struct node* n = NULL;
    for (unsigned int i = 0; i < MAX_SUBPROGRAMS; i++)
    {
        if (!strcmp(name, table[i].key))
            n = &table[i];
    }

    // Subroutine not found
    if (!n)
        return -1;

    // Copy args into subroutine's local buffer
    char* local_argbuf = n->prog.arg_str;
    for (unsigned int i = 0; i < argc; i++)
    {
        n->prog.argv[i] = local_argbuf;
        unsigned int arg_len = strlen(argv[i]);
        memcpy(local_argbuf, argv[i], arg_len);
        local_argbuf += arg_len;
        *local_argbuf++ = '\0';
    }
    n->prog.argc = argc;
    n->prog.subroutine(n->prog.argv, n->prog.argc);

    return 0;
}