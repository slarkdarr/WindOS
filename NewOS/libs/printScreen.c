#include "../library.h"

void printScreen (char a[50], int pos, int clr) {
    int i = 0;
    int loc = 0xB000;

    while (a[i]!='\0' ){
        putInMemory(loc,pos,a[i]);
        pos++;
        putInMemory(loc,pos,clr);
        pos++;
        i++;
    }
}