#include <stdlib.h>
#include <ctype.h>

int atoi(const char* str)
{
    int conv_val = 0;
    unsigned char sign = 0;
    if (!str)
        return 0;

    // Discard all whitespace characters
    while ((*str == ' ' || *str == '\t') && *str) str++;

    // Check if first character is a minus
    if (*str == '-')
    {
        sign = 1;
        str++;
    }

    // Parse decimal number
    while (*str)
    {
        if (isdigit((int) *str))
        {
            conv_val *= 10;
            conv_val += *str - 48;
        }
        else
        {
            break;
        }
        str++;
    }

    if (sign)
    {
        conv_val = ~conv_val;
        conv_val++;
    }
    return conv_val;
}