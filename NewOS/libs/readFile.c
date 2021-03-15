#include "../library.h"

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
        // printString("notfound\r\n");
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
