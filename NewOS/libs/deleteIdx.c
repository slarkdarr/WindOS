#include "../library.h"

void deleteIdx(char Idx,char*dir,int*success){
    if (dir[Idx*16 + 1] == 0xFF){
        deleteFolderIdx(Idx,dir,success);
    }
    else {
        deleteFileIdx(Idx,dir,success);
    }
}