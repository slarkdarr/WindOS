#include "../library.h"

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