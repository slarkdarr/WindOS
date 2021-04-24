#include "../library.h"

int main(){
    char args[512], cD[512],dir[1024];
    char idx;
    int succ;
    readSector(args,0x105);
    readSector(cD,0x104);
    readSector(dir,0x101);
    readSector(dir+512,0x102);

    if (cD[0] == 0x0) cD[0] = 0xFF;

    if(args[32] == 0x0){
        cD[0] = 0xFF;
        writeSector(cD,0x104);
    }else{
        idx = getPathIndex(&args[32],dir,cD[0]);
        if (idx == 0xFE){
            printString("Folder not found\r\n");
        }
        else if (idx != 0xFF && dir[idx*16+1] != 0xFF){
            printString("Not a folder\r\n");
        }
        else{
            cD[0] = idx;
            writeSector(cD,0x104);
        }
    }
    executeProgram("shell\0",0x2000,&succ,0xFF);
}