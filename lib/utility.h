#ifndef utility_h
#define utility_h

int strlen(char *a);
int strComp(char *a,char *b);
int strCompLimit(char*a,char*b,int lim);
void clearScreen();
void clear(char *buffer, int length);
void executeProgram(char* filename,int segment,int *success, char parentIndex);

#endif