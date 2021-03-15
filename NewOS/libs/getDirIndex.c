#include "../library.h"

char getDirIndex(char *path, char* dir, char parentIndex){
    int i,j;
    if (strComp(path,"..")){
        if (parentIndex == 0xFF) return parentIndex;
        else return dir[parentIndex * 16];
    }
    else if (strComp(path,".")){
        return parentIndex;
    }
    for (i = 0; i < 64; i ++){
        if (dir[i*16] == parentIndex){
            if (strComp(path,dir + (i*16 + 2)) || strCompLimit(path,dir + (i*16 + 2),14)){
                // printString("ada");
                // for (j = 0; j <14;j++){
                //     printChar(dir+i*16+2+j);
                // }
                return i;
            }
        }
    }
    return 0xFE; // not found
}