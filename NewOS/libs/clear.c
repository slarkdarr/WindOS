#include "../library.h"

void clear(char *buffer, int length){
    int i = 0;
    while (i < length)
    {
        buffer[i++] = 0;
    }
}