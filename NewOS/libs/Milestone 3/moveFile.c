#include "../library.h"

void moveFile(char *path,char *targetFolder, int *success, char parentidx){
    char dir[1024];
    char targetdir_idx, fileidx;
    
    readSector(dir,0x101);
    readSector(dir + 512,0x102);
    
    //QIL ISI INI YA
    fileidx = getPathIndex(path,dir,parentidx);
    if (fileidx== 0xFE){
        *success = -1; //FILE TIDAK KETEMU
        return;
    }
    //QIL ISI INI YA
    targetdir_idx = getPathIndex(targetFolder,dir,parentidx);
    if (targetdir_idx == 0xFE){
        *success = -2; //FOLDER TIDAK KETEMU
        return;
    }

    if (dir[targetdir_idx*16 + 1] != 0xFF){
        printString("Dest is not folder");
        *success = -1;
        return;
    }

    dir[fileidx * 16] = targetdir_idx;
    writeSector(dir,0x101);
    writeSector(dir + 512, 0x102);
    *success = 1;
}