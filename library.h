#ifndef LIBRARY_H
#define LIBRARY_H

#include "./lib/teks.h"
#include "./lib/fileIO.h"
#include "./lib/folderIO.h"
#include "./lib/matematika.h"
#include "./lib/utility.h"

void handleInterrupt21 (int AX, int BX, int CX, int DX);
void defaultDir();
void printBootScreen();
void printScreen (char a[50], int pos, int clr);
void _executeProgram(char* filename, int segment, int* success, char parentIndex);

#endif
