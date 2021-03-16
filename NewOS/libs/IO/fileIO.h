#ifndef FILEIO_H
#define FILEIO_H

void moveFile(char *path, char *targetFolder, int *success, char parentIndex);
void copyFile(char *path, char *targetFolder, int *success, char parentIndex);
void writeFile(char *buffer, char *path, int *success, char parentIndex);
void readFile(char *buffer, char *path, int *success, char parentIndex);
void deleteFileIdx(char Idx,char* dir,int*success);

#endif