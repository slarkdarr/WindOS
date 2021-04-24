#include "../library.h"

void printChar(char c){
    if (c == 0xD){
        interrupt(0x10, 0xE00 + '\r',0,0,0);
        interrupt(0x10, 0xE00 + '\n',0,0,0);
    }
    else if (c == 0xA){
        //
    }
    else{
    interrupt(0x10, 0xE00 + c,0,0,0);
    }
}