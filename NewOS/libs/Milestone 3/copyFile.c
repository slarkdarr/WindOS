#include "../library.h"

void copyFile(char *path, char *targetFolder, int *success, char parentIndex){
    char isiFile[512*16];
    int slash,i,pjg,targetIdx;
    char dir[1024];
    char writeFilePath[32];
    char filename[14];
    slash = 0;
    i = 0;
    readSector(dir,0x101);
    readSector(dir+512,0x102);
    while (path[i] != 0x0){
        if (path[i] == '/'){
            slash = i;
        }
        i++;
    }
    targetIdx = getPathIndex(targetFolder,dir,parentIndex);
    if (targetIdx == 0xFE){
        *success = -4; //not found
        return;
    }
    if (dir[targetIdx*16 + 1] != 0xFF){
        *success = -4; //not a folder
        return;
    }
    i=0;
    clear(filename,14);
    while (path[slash+i] != 0x0){
        filename[i] = path[slash + i];
        i++;
    }
    filename[i] = 0x0;
    clear(isiFile,512*16);
    clear(writeFilePath,32);
    readFile(isiFile,path,*success,parentIndex);
    pjg = strlen(targetFolder);
    copy(targetFolder,targetFolder + pjg,writeFilePath);
    writeFilePath[pjg] = '/';
    copy(filename,filename+strlen(filename),writeFilePath + pjg + 1);
    writeFile(isiFile,writeFilePath,success,parentIndex);
}