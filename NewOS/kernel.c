#include "library.h"

int main () {
    int done;
    makeInterrupt21();
    defaultDir();
    printBootScreen();
    interrupt(0x16,0x0000,0,0,0);
    clearScreen();
    _executeProgram("shell",0x2000,&done,0xFF);
    while (1);
}

// // void readSector(char *buffer, int sector){}
