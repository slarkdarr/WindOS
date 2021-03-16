#include "../library.h"

int main(){
    char dir[1024], cD[512], isi[64], idx, args[512];
    int i;
    readSector(args,0x105);
    readSector(cD,0x104);
    readSector(dir,0x101);
    readSector(dir+512,0x102);
    clear(isi, 64);

    if (cD[0] == 0x0){
        cD[0] = 0xFF;
    }
    if (args[32] != 0x0){
        // printString("ARGS :");
        // printline(&args[32]);
        idx = getPathIndex(&args[32],dir,cD[0]);
    }else{
        // printString("NOARGS\r\n");
        idx = cD[0];
    }

    if (idx == 0xFE){
        printString("Folder not found\r\n");
    } else{
        i = 0;
        // if (idx == 0xFF) printString("root\r\n");
        while (i < 64){
            // if (dir[i*16] == 0xFF) printString("HIT");
            if (dir[i*16] == idx){
                if(dir[i*16+1] == 0xFF){
                    printChar('/');
                }
                printString(dir+i*16+2);
                printString(" ");
            }
            i++;
        }
        printString("\r\n");
    }
    executeProgram("shell\0",0x2000,&i,0xFF);
}
