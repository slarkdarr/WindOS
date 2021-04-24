#include "../library.h"

void printDir(char curDir); 
void splitArgs(char *path,char* result);

int main(){
    int success, runHere, count;
    char read[16 * 32];
    char cD[512], args[512];
    char rundir;

    readSector(cD,0x104); //currentDirectory

    if(cD[0] == 0x0){
        cD[0] = 0xFF;
    }

    while (1){
        printString("WindOS> ");
        printDir(cD[0]);
        printString("$ ");
        clear(read,512);
        readString(read);
        printString("\r\n");
        // printline(read);

        clear(args,512);
        splitArgs(read,args);
        
        writeSector(cD,0x104); //currentDirectory
        writeSector(args,0x105); //args
        rundir = (read[0] == '.' && read[1] == '/');

        executeProgram(rundir ? &args[2] : args,0x3000,&success,rundir ? cD[0] : 0xFF);
        if (success != 1 && *args){
            printString("Invalid command\r\n");
        }
    }
}

void printDir(char curDir){
    char parent;
    char dir[1024];
    readSector(dir,0x101);
    readSector(dir+512,0x102);
    if (curDir != 0xFF){
        parent = getDirIndex("..\0",dir,curDir);
        if (parent != 0xFF){
            printDir(parent); //recc sampe root dir
        }
    }
    interrupt(0x21,0x0,"/",0x0,0x0);
    if (curDir != 0xFF){
        interrupt(0x21,0x0,&dir[curDir*16 + 2],0x0,0x0);
    }
}

void splitArgs(char *path, char *result)
{
    char *lastSpace = path;
    int cnt = 0;
    while (1)
    {
        if (*path == ' ' || !*path)
        {
            copy(lastSpace, path, result);
            lastSpace = path + 1;
            result += 32;
            if (!*path || ++cnt >= 16)
            {
                return;
            }
        }
        ++path;
    }
}
