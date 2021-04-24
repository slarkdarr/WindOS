#include "../library.h"

int main(){
    char args[512],cD[512];
    int resp=0;

    readSector(args,0x105);
    readSector(cD,0x104);

    if (cD[0] == 0x0) cD[0] = 0xFF;
    // if (cD[0] == 0xFF) printline("Parent!");
    if (args[32] != 0x0){
        delete(&args[32],&resp,cD[0]);
        if (resp == 1){
            printString(&args[32]);
            printline(" berhasil dihapus!");
        }
        else{
            printline("Error");
        }
    }
    else{
        printline("Usage : rm [FILE/FOLDER]");
    }
    executeProgram("shell\0",0x2000,&resp,0xFF);
}