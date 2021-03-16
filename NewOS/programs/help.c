#include "../library.h"

int main(){

    int ints;
    
    printline("Here are the available commands: ");
    printline("- ls");
    printline("- ln [file1] [file2]");
    printline("- clear");
    printline("- cat [file]");
    printline("- cd [path or directory]");
    printline("- echo [text]");
    printline("- editor [optional file]");

    printString("\r\n");
    executeProgram("shell\0",0x2000,&ints,0xFF);
}
