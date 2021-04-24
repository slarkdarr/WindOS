#include "../library.h"

int main(){
    char arguments[512];
    char cD[512];
    int hasil = 0;

    readSector(arguments,0x105);
    readSector(cD,0x104);

    if (!cD[0]) cD[0] = 0xFF;
    if (!arguments[32] || !arguments[64]){
        printline("Invalid argument");
        // mv <namafile> <namafolder>
    }
    else{
        moveFile(arguments + 32, arguments + 32 * 2, &hasil, cD[0]);
        switch(hasil){
            case 1:
                printline("File berhasil dipindahkan");
                break;
            case -1:
                printString("File ");
                printString(&arguments[32]);
                printline(" not found");
                break;
            case -2:
                printString("Folder ");
                printString(&arguments[64]);
                printline(" found");
                break;
            default:
                printline("Error");
        }
    }
    executeProgram("shell\0",0x2000,&hasil,0xFF);
}