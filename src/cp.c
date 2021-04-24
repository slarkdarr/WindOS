#include "../library.h"

int main(){
    char args[512];
    char cD[512];
    int success;
    readSector(cD,0x104);
    readSector(args,0x105);

    if (cD[0] == 0x0){
        cD[0] = 0xFF;
    }

    if (args[32]==0x0 || args[64]==0x0){
        printline("Give input file and copy destination");
    }
    else{
        copyFile(args+32,args+64,&success,cD[0]);
        if (success==1){
            printline("Copied Successfully");
        }
        else if (success == -4){
            printline("Destination Invalid");
        }
        else if (success = -1){
            printline("Copy object not found");
        }
        else{
            printline("error");
        }
    }
    executeProgram("shell\0",0x2000,&success,0xFF);
}