#include "../library.h"

int strlen(char *s){
    int i = 0;
    char *p = s;
    while(*p != '\0'){
        p++;
        i++;
    }
    return i;
}