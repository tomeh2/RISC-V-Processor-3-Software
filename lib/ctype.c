#include <ctype.h>

int isdigit(int c)
{
    return c >= 48 && c <= 57 ? 1 : 0;
}
