#include "../library.h"

int main(){

    int ints;
    
    printline("Here are the available commands: ");
    printline("- ls");
    printline("- ln [file1] [file2]");
    printline("- cls");
    printline("- cat [file]");
    printline("- cd [path or directory]");
    printline("- wim [optional file]");
    printline("- mkdir [directory]");
    printline("- mv [file] [destination directory]");
    printline("- rm [file or directory]");
    printline("- cp [file] [destination directory]");

    printString("\r\n");
    executeProgram("shell\0",0x2000,&ints,0xFF);
}
