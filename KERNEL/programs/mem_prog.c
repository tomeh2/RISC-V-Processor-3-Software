#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * hex2int
 * take a hex string and convert it to a 32bit number (max 8 hex digits)
 */
uint32_t hex2int(const char *hex) {
    uint32_t val = 0;
    while (*hex) {
        // get current character then increment
        char byte = *hex++; 
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;    
        // shift 4 to make space for new digit, and add the 4 bits of the new digit 
        val = (val << 4) | (byte & 0xF);
    }
    return val;
}

void memr_main(const char** argv, unsigned int argc)
{
    if (argc < 2)
        return;
    
    volatile uint32_t* base = (uint32_t*) hex2int(argv[0]);
    printf("\n\r");
    for (unsigned int i = 0; i < 8; i++)
    {
        for (unsigned int j = 0; j < 8; j++)
        {
            printf("%x ", *base);
            base++;
        }   
        printf("\n\r");
    }
}