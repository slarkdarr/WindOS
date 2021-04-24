#include "../library.h"

int main(){
    char cD[512], args[512];
    int success;
    readSector(cD,0x104);
    readSector(args,0x105);

    if (cD[0] == 0x0) cD[0] = 0xFF;

    if(args[32] == 0x0){
        printline("kosong");
    }
    else{
        makeDir(&args[32],&success,cD[0]);
        if (success == 1){
            printString(&args[32]);
            printline("sukses");
        }
        else if (success == -5){
            printline("Namanya kepanjangan");
        }
        else if (success == -1){
            printline("Already exist");
        }
        else if (success == -4){
            printline("Destination not found");
        }
    }
    executeProgram("shell\0",0x2000,&success,0xFF);
}