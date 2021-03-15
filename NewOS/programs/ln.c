#include "../library.h"

int main(){

    //Dari cat
    char args[512], Buffer[512 * 16], cD[512];
    int success;
    clear(Buffer,512);
    readSector(cD,0x104);
    readSector(args,0x105);
    if (args[32] == 0x0){
        printString("Masukkan nama filenya bro\r\n");
    } else{
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

    //Dari editor
    writeFile(file,filename,&succ,cD[0]);
    if (succ == 1){
        printline("Successfully saved");
    }
    else{
        printline("Error saving");
    }
}