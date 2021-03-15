#ifndef LIBRARY_H
#define LIBRARY_H

// #include "libs/tools.h"
// #include "libs/textIO.h"
// #include "libs/fileIO.h"
// #include "libs/folderIO.h"
// #include "libs/math.h"

void moveFile(char *path, char *targetFolder, int *success, char parentIndex);
void copyFile(char *path, char *targetFolder, int *success, char parentIndex);
void writeFile(char *buffer, char *path, int *success, char parentIndex);
void readFile(char *buffer, char *path, int *success, char parentIndex);
void deleteFileIdx(char Idx,char* dir,int*success);

// void makeDir(char *foldername, char *success, char parentIndex);
void delete(char* filename, int* success, char parentIndex);
// void deleteIdx(char Idx, char* dir,int* success);
// void deleteFolder(char *path, char *resultCode, char parentIndex);
// void deleteFolderIdx(char Idx);
// void listContent(char Idx,char* dir);
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