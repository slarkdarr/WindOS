#include "library.h"
void handleInterrupt21 (int AX, int BX, int CX, int DX);
void defaultDir();
void printBootScreen();
void printScreen (char a[50], int pos, int clr);
void _executeProgram(char* filename, int segment, int* success, char parentIndex);

int main () {
    int done;
    makeInterrupt21();
    defaultDir();
    printBootScreen();
    interrupt(0x16,0x0000,0,0,0);
    clearScreen();
    _executeProgram("shell",0x2000,&done,0xFF);
    while (1);
}

void defaultDir(){
  char cD[512];
  clear(cD,512);
  writeSector(cD,0x104);
}

void handleInterrupt21 (int AX, int BX, int CX, int DX) {
    char AL, AH;
    AL = (char) (AX);
    AH = AX >> 8;
  switch (AL) {
    case 0:
      printString(BX);
      break;
    case 1:
      readString(BX);
      break;
    case 2:
      readSector(BX, CX);
      break;
    case 3:
      writeSector(BX, CX);
      break;
    case 4:
      readFile(BX, CX, DX,AH);
      break;
    case 5:
      writeFile(BX, CX, DX,AH);
      break;
    case 6:
      _executeProgram(BX, CX, DX,AH);
      break;
    default:
      printString("Invalid interrupt");
  }

}

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


// // void readSector(char *buffer, int sector){}
void printBootScreen(){
    int pos = 0x8000;
    
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("           ___       _______         ________________ ________          ",pos,0x2);pos+=0xA0;
    printScreen("           __ |     / /___(_)_______ ______  /__  __ \\__  ___/         ",pos,0x2);pos+=0xA0;
    printScreen("           __ | /| / / __  / __  __ \\_  __  / _  / / /_____ \\         ",pos,0x2);pos+=0xA0;
    printScreen("           __ |/ |/ /  _  /  _  / / // /_/ /  / /_/ / ____/ /           ",pos,0x2);pos+=0xA0;
    printScreen("           ____/|__/   /_/   /_/ /_/ \\__,_/   \\____/  /____/          ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                      Please press ENTER to continue...                 ",pos,0xC);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    
    

}

void printScreen (char a[50], int pos, int clr) {
    int i = 0;
    int loc = 0xB000;

    while (a[i]!='\0' ){
        putInMemory(loc,pos,a[i]);
        pos++;
        putInMemory(loc,pos,clr);
        pos++;
        i++;
    }
}
