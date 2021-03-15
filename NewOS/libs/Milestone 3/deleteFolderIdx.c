#include "../library.h"

void deleteFolderIdx(char dirIdx,char* dir, int* success){
    char name[14];
    int j,i;

    for (i=0; i < 64; i++){
        if (dir[i*16] == dirIdx){
            deleteIdx(i,dir,success);
        }
    }

    for (j = 0; j < 16;j++){
        dir[dirIdx*16 + j] = 0x0;
    }
}
