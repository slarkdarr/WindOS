#include "../library.h"

int main(){
    char arguments[512];
    int i=32;
    readSector(arguments,0x105);
    
    while(arguments[i]){
        printString(&arguments[i]);
        if(i!=512) printString(" ");
        i+=32;
    }
    printString("\r\n");
    executeProgram("shell\0",0x2000,&i,0xFF);
}