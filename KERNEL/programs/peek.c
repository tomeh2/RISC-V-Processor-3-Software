#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/**
 * hex2int
 * take a hex string and convert it to a 32bit number (max 8 hex digits)
 */
extern uint32_t hex2int(const char *hex);

void peek_main(char** argv, unsigned int argc)
{
    unsigned char flags = 0;
    if (argc < 1)
    {
        printf("peek <address [hex]> <-h optional>");
        return;
    }

    if (argc >= 2)
    {
        if (!strcmp(argv[1], "-h"))
            flags |= 1;
    }

    volatile uint32_t* base = (uint32_t*) hex2int(argv[0]);
    if (flags & 1)
        printf("%0x08x: 0x%08x\n\r", base, *base);
    else
        printf("%0x08x: %d\n\r", base, *base);
}