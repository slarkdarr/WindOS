#include "../library.h"

void _executeProgram(char* filename, int segment, int* success, char parentIndex){
    int i=0;
    char readBuffer[512*16];
    
    // if (parentIndex == 0xFF) printString("Parent");
    readFile(readBuffer,filename,success,parentIndex);
    if(*success == 1){
        // printString("anjing");
        for (i = 0; i<512*16;i++){
            putInMemory(segment,i,readBuffer[i]);
        }
        launchProgram(segment);
    }
}