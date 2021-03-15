#include "../library.h"

int main(){

    //Baca file
    char args[512], Buffer[512 * 16], cD[512];
    int success;
    clear(Buffer,512);
    readSector(cD,0x104);
    readSector(args,0x105);
    if (args[32] == 0x0 || args[64] == 0x0){
        printString("Masukkan nama filenya bro\r\n");
    } else {
        // printString(&args[32]);
        readFile(Buffer,&args[32],&success,cD[0]);
        if (success == 1){
            printString(&args[32]);
            printString(" : \r\n");
            printString(Buffer);
            printString("\r\n");
        }else{
            printline("Something is wrong\r\n");
        }
    }

    //Tulis file
    writeFile(Buffer,&args[64],&success,cD[0]);
    if (success == 1){
        printline("Successfully saved");
    }
    else{
        printline("Error saving");
    }

    clearScreen();
    executeProgram("shell",0x2000,&success,0xFF);

}