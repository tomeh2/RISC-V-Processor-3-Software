#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * hex2int
 * take a hex string and convert it to a 32bit number (max 8 hex digits)
 */
uint32_t hex2int(const char *hex);

void poke_main(char** argv, unsigned int argc)
{
    if (argc < 2)
    {
        printf("poke <address [hex]> <value [dec]>");
        return;
    }

    volatile uint32_t* base = (uint32_t*) hex2int(argv[0]);
    uint32_t value = atoi(argv[1]);
    *base = value;
}