#include "../library.h"

void copy(char *from, char *to, char *result)
{
    int i;
    for (i = 0; i < to - from; i++)
    {
        result[i] = from[i];
    }
    result[i] = 0;
}