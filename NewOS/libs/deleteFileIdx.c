#include "../library.h"

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