#include "../library.h"


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