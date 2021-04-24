#include "../library.h"

int strCompLimit(char* a, char* b, int limit){
    int i;
    for (i = 0; i < limit; i ++){
            if(a[i] != b[i]) return 0;
        }
    return 1;
}
