#include "../library.h"

void makeDir(char* foldername,int* success,char parentIndex){
    int ada,sama,i,j,slash;
    char dir[1024];
    char dirname[14];
    char dirIdx;
    readSector(dir,0x101);
    readSector(dir+512,0x102);
    slash = -1;
    i=0;
    ada = 0;
    while(foldername[i] != 0x0){
        if (foldername[i] == '/'){
            slash = i;
        }
        i++;
    }
    // printString("1");
    if (slash == -1){
        dirIdx = getPathIndex(foldername,dir,parentIndex);
        if (dirIdx != 0xFE){
            *success = -1; //Error
            return;
        }
        dirIdx = parentIndex;
    }else{
        for (j=0; j < slash;j++){
            dirname[j] = foldername[j];
        }
        dirname[j] = 0x0;
        dirIdx = getPathIndex(dirname,dir,parentIndex);
        if (dirIdx == 0xFE){
            *success = -4; // Parent dir nggak error
            return;
        }
    }
    // printline("2");

    if (strlen(foldername) - strlen(dirname) > 14){
        *success = -5;
        return;
    }
    for (i=0;i<1024;i+=16){
        if (dir[i] == 0x0){     
            dir[i] = dirIdx;
            dir[i+1] = 0xFF;
            j=0;
            while(foldername[j + slash + 1] != 0x0){
                dir[i+2+j] = foldername[j + slash + 1];
                j++;
            }
            dir[i+2+j] = 0x0;
            writeSector(dir,0x101);
            writeSector(dir+512,0x102);
            return;
        }
    }
}
