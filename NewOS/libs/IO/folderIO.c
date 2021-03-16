// #include "../library.h"

void makeDir(char* foldername,int* success,char parentIndex) {
    int ada,sama,i,j,slash;
    char dir[1024];
    char dirname[14];
    char dirIdx;
    readSector(dir,0x101);
    readSector(dir+512,0x102);
    slash = -1;
    i=0;
    ada = 0;
    // printline(foldername);
    while(foldername[i] != 0x0){
        if (foldername[i] == '/'){
            slash = i;
        }
        i++;
    }
    // printString("im here now");
    // print(foldername);
    if (slash == -1){
        dirIdx = getPathIndex(foldername,dir,parentIndex);
        if (dirIdx != 0xFE){
            *success = -1; //kalo file udh ada error
            // printString("\r\nthere");
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
            *success = -4; // kalo bapaknya gada error
            // printString("\r\nnofa there");
            return;
        }
    }
    // printline("hai");
    // printline(foldername+slash);

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
            // printString(foldername);
            // printString(" ditambah\r\n");
            writeSector(dir,0x101);
            writeSector(dir+512,0x102);
            return;
        }
    }
}


void delete(char* filename, int* success, char parentIndex){
    char dir[1024];
    char dirIdx;
    readSector(dir,0x101);
    readSector(dir+512,0x102);
    // printString("Deleting : ");
    // printline(filename);
    
    dirIdx = getPathIndex(filename,dir,parentIndex);
    
    if (dirIdx == 0xFE){
        // printline("File not found");
        *success = -3;
        return;
    }

    deleteIdx(dirIdx,dir,success);
    *success = 1;
    writeSector(dir,0x101);
    writeSector(dir+512,0x102);
}

void deleteIdx(char Idx,char*dir,int*success){
    if (dir[Idx*16 + 1] == 0xFF){
        deleteFolderIdx(Idx,dir,success);
    }
    else {
        deleteFileIdx(Idx,dir,success);
    }
}


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

char getPathIndex(char*path, char* dir, char parentIndex){
    int i,j,final;
    char searchIdx;
    char temp[15];
    final = 0x0; // maksud final adalah file tersebut di dir tersebut
    i = 0;
    while(i < 14 && path[i] != '/' && path[i] != 0x0){
        temp[i] = path[i];
        i++;
    }
    if (path[i] == 0x0) final = 1;
    // if (final == 1) printString("its final yo");
    temp[i] = 0x0;
    // printString(temp);
    j = i+1;
    searchIdx = getDirIndex(temp,dir,parentIndex);
    // printString("THECHAR");
    // printChar(searchIdx);
    if (searchIdx == 0xFE) return 0xFE;// not found 
    if (final) return searchIdx;
    return getPathIndex(path+j,dir,searchIdx); //jika awalnya mencari /bin/file skrg mencari /file di idxnya bin saja
}

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
