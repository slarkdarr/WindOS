#include "../library.h"

int main(){
    char args[512], Buffer[512 * 16], cD[512];
    int success;
    clear(Buffer,512);
    readSector(cD,0x104);
    readSector(args,0x105);
    if (args[32] == 0x0){
        printString("Please input a file name\r\n");
    }else{
        readFile(Buffer,&args[32],&success,cD[0]);
        if (success == 1){
            printString(&args[32]);
            printString(" : \r\n");
            printString(Buffer);
            printString("\r\n");
        }else{
            printline("File not found\r\n");
        }
    }
    executeProgram("shell\0",0x2000,&success,0xFF);
}