#include "../library.h"

int mod(int a, int b)
{   
    int mod=a;
    while (mod >= b)
    {
        mod -= b;
    }
    return mod;
}