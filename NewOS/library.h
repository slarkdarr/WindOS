#ifndef LIBRARY_H
#define LIBRARY_H

void handleInterrupt21 (int AX, int BX, int CX, int DX);
void defaultDir();
void printBootScreen();
void printScreen (char a[50], int pos, int clr);
void _executeProgram(char* filename, int segment, int* success, char parentIndex);

void moveFile(char *path, char *targetFolder, int *success, char parentIndex);
void copyFile(char *path, char *targetFolder, int *success, char parentIndex);
void writeFile(char *buffer, char *path, int *success, char parentIndex);
void readFile(char *buffer, char *path, int *success, char parentIndex);

char getDirIndex(char *path, char* dir, char parentIndex);
char getPathIndex(char*path, char* dir, char parentIndex);

int mod(int a, int b);
int div(int a, int b);

void printChar(char c);
void printString(char *string);
void readString(char *string);
void readSector(char *buffer, int sector);
void writeSector(char *buffer, int sector);
void printline(char *string);
void copy(char *from, char *to, char *result);

int strlen(char *a);
int strComp(char *a,char *b);
int strCompLim(char*a,char*b,int lim);
void clearScreen();
void clear(char *buffer, int length);
void executeProgram(char* filename,int segment,int *success, char parentIndex);

#endif