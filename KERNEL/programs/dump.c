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
        printf("dump <start_addr [hex]> <length>\n\r");
        return;
    }
    
    volatile uint32_t* base = (uint32_t*) hex2int(argv[0]);
    unsigned int length = (unsigned int) atoi(argv[1]);

    if (length > MAX_LENGTH)
        return;

    unsigned int rows = length / VALUES_PER_ROW;
    unsigned int last_row_values = length % VALUES_PER_ROW;

    for (unsigned int i = 0; i <= rows; i++)
    {
        printf("0x%08x: ", base);

        unsigned int values_in_row = VALUES_PER_ROW;
        if (i == rows - 1)
            values_in_row = last_row_values;

        for (unsigned int j = 0; j < values_in_row; j++)
        {
            printf("0x%08x ", *base);
            base++;
        }   
        printf("\n\r");
    }
}