#include "../library.h"

void clearScreen(){
    int i=0,j=100;

    while(i < 4000){
        putInMemory(0xB000,0x8000+i,'\0');
        i++;
        putInMemory(0xB000,0x8000+i,0x7);
        i++;
    }
    while(--j){
        ;
    }
    interrupt(0x10,0x2*256 + 0x0,0,0x0,0);
    return;
}