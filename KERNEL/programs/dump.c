#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * hex2int
 * take a hex string and convert it to a 32bit number (max 8 hex digits)
 */
uint32_t hex2int(const char *hex);

#define VALUES_PER_ROW 4
#define MAX_LENGTH 1024

void dump_main(const char** argv, unsigned int argc)
{
    if (argc < 2)
    {
        printf("dump <start_addr [hex]> <length [dec]>\n\r");
        return;
    }
    volatile uint32_t* addr = (uint32_t*) hex2int(argv[0]);
    unsigned int length = (unsigned int) atoi(argv[1]);

    if (length > MAX_LENGTH)
    {
        printf("Dump length too large (max %d)!\n\r", MAX_LENGTH);
        return;
    }

    for (unsigned int i = 0; i < length; i++)
    {
        if (!(i % VALUES_PER_ROW))
        {
            printf("\n\r0x%08x: ", addr);
        }
        printf("0x%08x ", *addr);
        addr++;
    }
}