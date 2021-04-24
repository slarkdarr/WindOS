#ifndef FOLDERIO_H
#define FOLDERIO_H

void makeDir(char* foldername, int* success, char parentIndex);
void delete(char* filename, int* success, char parentIndex);
void deleteIdx(char Idx, char* dir, int* success);
void deleteFolder(char *path, char *resultCode, char parentIndex);
void deleteFolderIdx(char dirIdx, char* dir, int* success);
void listContent(char Idx,char* dir);
char getDirIndex(char* path, char* dir, char parentIndex);
char getPathIndex(char* path, char* dir, char parentIndex);

#endif
