#include "../library.h"

void printString(char *string){
    int i = 0;
    while(string[i] != '\0'){
        printChar(string[i]);
        i++;
    }
}