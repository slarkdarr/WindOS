#include "../library.h"

char getPathIndex(char*path, char* dir, char parentIndex){
    int i,j,final;
    char searchIdx;
    char temp[15];
    final = 0x0; // address file di directory
    i = 0;
    while(i < 14 && path[i] != '/' && path[i] != 0x0){
        temp[i] = path[i];
        i++;
    }
    if (path[i] == 0x0) final = 1;
    temp[i] = 0x0;
    j = i+1;
    searchIdx = getDirIndex(temp,dir,parentIndex);
    if (searchIdx == 0xFE) return 0xFE; // Path not found 
    if (final) return searchIdx;
    return getPathIndex(path+j,dir,searchIdx);
}