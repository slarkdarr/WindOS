#include "./fileIO.h"

void copyFile(char *path, char *targetFolder, int *success, char parentIndex){
    char isiFile[512*16];
    int slash,i,p,targetIdx;
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
    p = strlen(targetFolder);
    copy(targetFolder,targetFolder + p,writeFilePath);
    writeFilePath[p] = '/';
    copy(filename,filename+strlen(filename),writeFilePath + p + 1);
    writeFile(isiFile,writeFilePath,success,parentIndex);
}


void writeFile(char*buffer, char* filename, int* success, char parentIndex){
    int i, j, k, l, m, slash, iter, len;
    char map[512];
    char dir[1024];
    char sector[512];
    char dirname[512];
    char subBuff[512];
    char toWrite[512],debug[10];
    char dirIdx;
    readSector(map,0x100);
    readSector(dir,0x101);
    readSector(dir + 512,0x102);
    readSector(sector,0x103);
    clear(debug,10);
    slash = -1;
    i=0;
    // printString("1");
    while(filename[i] != 0x0 && i < 14){
        if (filename[i] == '/'){
            slash = i;
        }
        i++;
    }
    // printString("2");

    if (slash == -1){
        dirIdx = getPathIndex(filename,dir,parentIndex);
        if (dirIdx != 0xFE){
            *success = -1; //kalo error
            return;
        }
        dirIdx = parentIndex;
    }else{
        for (j=0; j < slash;j++){
            dirname[j] = filename[j];
        }
        dirname[j] = 0x0;
        dirIdx = getPathIndex(dirname,dir,parentIndex);
        debug[0]=dirIdx;
        if (dirIdx == 0xFE || dir[dirIdx*16 + 1] != 0xFF){
            *success = -4; // parent dir nggak ada error
            printString("Folder not found\r\n");
            return;
        }
    }

    if (*success != -1 && *success != -4){
        k=0;
        while (dir[k*16] != 0x0 && dir[k*16+2] != 0x0 && k < 64){
            k++;
        }
        if (k > 63){
            *success = -2;
            return;
        }
        l=0;
        while(sector[l*16] != 0x0 && l < 32){
            l++;
        }
        if (l > 31){
            *success = -3;
            return;
        }
        dir[k*16] = dirIdx;
        dir[k*16 + 1] = l;
        copy(dir+k*16, dir+k*16+10,debug);
        iter = 0;
        while (iter < 14 && filename[slash + 1 + iter] != 0x0){
            dir[k*16 + 2 + iter] = filename[slash + 1 + iter];
            iter++;
        }
        dir[k*16 + 2 + iter] = 0x0;
        len = div(strlen(buffer),512) + 1;
        if (len > 16){
            *success = -3;
            return;
        }
        iter = 0;
        for (iter = 0; iter < len; iter++){
            clear(toWrite,512);
            m = 0;
            while (m < 512 && buffer[m + iter*512] != 0x0){
                toWrite[m] = buffer[m + iter*512];
                m++;
            }

            m=0;
            while(map[m] != 0x0 && m <512){
                m++;
            }

            writeSector(toWrite,m);
            map[m] = 0xFF;
            sector[l*16+iter] = m;
        }
        writeSector(map,0x100);
        writeSector(dir,0x101);
        writeSector(dir+512,0x102);
        writeSector(sector,0x103);
        *success = 1;
        return;
    }
}

void readFile(char *buffer, char* filename, int *success, char parentIndex){
    char dir[1024];
    char sector[512];
    int found = 0;
    char dirIdx,fileIdx;
    int i,j;

    readSector(dir,0x101);
    readSector(dir+512,0x102);

    dirIdx = getPathIndex(filename,dir,parentIndex);
    if (dirIdx == 0xFE){ // not found
        *success = -1;
        return;
    } 

    if (dir[dirIdx*16+1] == 0xFF){
        *success = -1;
        return;
    }

    readSector(sector,0x103);
    i = dir[dirIdx*16 + 1] * 16;
    j=0;
    while(j < 16 && sector[i+j] != 0x0){
        readSector(buffer + (j*512),sector[i+j]);
        j++;
    }
    *success =1;
}

void deleteFileIdx(char Idx,char* dir,int*success){
    char sector[512], map[512];
    char sect;
    int i;
    readSector(sector,0x103);
    readSector(map,0x100);
    sect = dir[Idx*16 + 1];
    i = 0;
    while (i < 16 && sector[sect*16 + i] != 0x0 ){
        map[sector[sect*16+i]] = 0x0;
        sector[sect*16 + i] = 0x0;
        i++;
    }
    for (i = 0; i < 16; i++){
        dir[Idx*16 + i] = 0x0;
    }
    writeSector(map,0x100);
    writeSector(sector,0x103);
}

void moveFile(char *path,char *targetFolder, int *success, char parentidx){
    char dir[1024];
    char targetdir_idx, fileidx;
    
    readSector(dir,0x101);
    readSector(dir + 512,0x102);
    
    fileidx = getPathIndex(path,dir,parentidx);
    if (fileidx== 0xFE){
        *success = -1; //FILE TIDAK KETEMU
        return;
    }

    targetdir_idx = getPathIndex(targetFolder,dir,parentidx);
    if (targetdir_idx == 0xFE){
        *success = -2; //FOLDER TIDAK KETEMU
        return;
    }

    if (dir[targetdir_idx*16 + 1] != 0xFF){
        printline(dir[targetdir_idx]);
        printString("Dest is not folder");
        *success = -1;
        return;
    }

    dir[fileidx * 16] = targetdir_idx;
    writeSector(dir,0x101);
    writeSector(dir + 512, 0x102);
    *success = 1;
}