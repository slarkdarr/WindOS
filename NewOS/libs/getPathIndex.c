#include "../library.h"

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