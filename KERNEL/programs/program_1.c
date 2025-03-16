#include <stdio.h>

void program_1_main(char** argv, unsigned int argc)
{
    printf("\n\rargc: %d\n\r", argc);
    for (unsigned int i = 0; i < argc; i++)
    {
        printf("arg %d: %s\n\r", i, argv[i]);
    }
}