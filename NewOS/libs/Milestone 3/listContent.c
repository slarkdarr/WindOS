#include "../library.h"

void listContent(char Idx,char* dir){
    int i;
    int j;
    for (i=0; i < 64;i++){
        if (dir[i*16] == Idx){
            if (dir[i*16 + 1] == 0xFF){
                interrupt(0x10,0xE00 + '/',0x0,0x0,0x0);
            }
            for (j=0; j < 14;j++){
                interrupt(0x10,0xE00 + dir[i*16 + j],0x0,0x0,0x0);
            }
        }
        interrupt(0x10,0xE00 + " ",0x0,0x0,0x0);

    }
}