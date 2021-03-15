// #include "../library.h"

int strlen(char *s){
    int i = 0;
    char *p = s;
    while(*p != '\0'){
        p++;
        i++;
    }
    // printChar(i);
    return i;
}

int strComp(char *a,char* b){
    int i = 0;
    int pja,pjb;
    pja = strlen(a);
    pjb = strlen(b);
    if (pja > pjb) return 0;
    else if (pjb > pja) return 0;
    else {
        for (i = 0; i < pja; i ++){
            // printChar(a[i]);
            // printString(" ");
            // printChar(b[i]);
            if(a[i] != b[i]) return 0;
        }
        return 1;
    }
}

int strCompLimit(char* a, char* b, int limit){
    int i;
    for (i = 0; i < limit; i ++){
            if(a[i] != b[i]) return 0;
        }
    return 1;
}


void clearScreen(){
    int i=0,j=100;

    while(i < 4000){
        putInMemory(0xB000,0x8000+i,'\0');
        i++;
        putInMemory(0xB000,0x8000+i,0x7);
        i++;
    }
    while(--j){
        ;
    }
    interrupt(0x10,0x2*256 + 0x0,0,0x0,0);
    return;
}

void clear(char *buffer, int length){
    int i = 0;
    while (i < length)
    {
        buffer[i++] = 0;
    }
}

void executeProgram(char *filename, int segment, int *success, char parentIndex)
{
    interrupt(0x21, (parentIndex << 8) + 0x06, filename, segment, success);
}
