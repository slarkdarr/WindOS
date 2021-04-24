#ifndef fileio_h
#define fileio_h

void copyFile(char *path, char *targetFolder, int *success, char parentIndex);
void writeFile(char *buffer, char *path, int *success, char parentIndex);
void readFile(char *buffer, char *path, int *success, char parentIndex);
void deleteFileIdx(char Idx,char* dir,int*success);
void moveFile(char *path, char *targetFolder, int *success, char parentIndex);

#endif