#include "../library.h"

void _executeProgram(char* filename, int segment, int* success, char parentIndex){
    int i=0;
    char Buffer[512*16];
    
    readFile(Buffer,filename,success,parentIndex);
    if(*success == 1){
        for (i = 0; i<512*16;i++){
            putInMemory(segment,i,Buffer[i]);
        }
        launchProgram(segment);
    }
}
