#include "../library.h"

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

    while(filename[i] != 0x0 && i < 14){
        if (filename[i] == '/'){
            slash = i;
        }
        i++;
    }


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