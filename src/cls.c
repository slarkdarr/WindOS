#include "../library.h"

int main(){
    int ints;
    clearScreen();
    executeProgram("shell\0",0x2000,&ints,0xFF);
}