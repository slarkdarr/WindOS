#include "../library.h"


int main(){
    char file[512*16], cD[512];
    char filename[40],args[512];
    int i = 0,succ,existing = 0,ada=0;
    int tes;
    char next;
    char dir[1024];
    readSector(dir,0x101);
    readSector(dir+512,0x102);
    readSector(args,0x105);
    readSector(cD,0x104);
    clear(file,512*16);
    clear(filename,14);
    if (args[32] != 0x0){
        // printString("ArgTaken");
        existing = 1;
        while(args[32 + i] != 0x0 && i < 14){
            filename[i] = args[32+i];
            // if (filename[i] == '/') slash = i;
            i++;
        }
        filename[i] = 0x0;
        readFile(file,filename,&succ,cD[0]);
    }
    clearScreen();
    i=0;
    printline("Editor text buatan rumahan");
    if (existing) {
        printString("Editing :");
        printline(filename);
    }
    printline("CTRL C = quit, CTRL S = save");
    if (succ == 1){
            ada = 1;
            i=0;
            while(file[i]){
                printChar(file[i]);
                i++;
            }
    }
    while(1){
        tes = interrupt(0x16,0,0,0,0);
        next = (char) tes;
        if (next == 0x3){
            clearScreen();
            executeProgram("shell",0x2000,&succ,0xFF);
        }
        else if (next == 0x13 && !existing){
            printString("\r\n");
            printString("Save as :");
            readString(filename);
            printline("");
            // printline(filename);
            if (strlen(filename) > 40){
                printString("Kepanjangan, Gagal\r\n");
            }
            else{
                writeFile(file,filename,&succ,cD[0]);
                if (succ == 1){
                    printline("Successfully saved");
                }
                else{
                    printline("Error saving");
                }
            }
            clearScreen();
            executeProgram("shell",0x2000,&succ,0xFF);
        }
        else if (next == 0x13 && existing){
            printString("\r\n");
            if (ada) printString("Updating ");
            else printString("Saving as ");
            printline(filename);
            if (ada){
                delete(filename,&succ,cD[0]);
            }
            succ = 0;
            writeFile(file,filename,&succ,cD[0]);
            clearScreen();
            executeProgram("shell",0x2000,&succ,0xFF);
        }
        else if (next == 0x8){
            if (i!=0){
                i-=1;
                file[i] = '\0';
                printString("\b \b");
            }
        }
        else{
            file[i] = next;
            i += 1;
            printChar(next);
        }
    }
}