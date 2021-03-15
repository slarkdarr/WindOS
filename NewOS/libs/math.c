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

int div(int a, int b)
{
    int div = 0;
    while (a >= b)
    {
        div+=1;
        a -= b;
    }
    return div;
}