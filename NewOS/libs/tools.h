#ifndef TOOLS_H
#define TOOLS_H


int strlen(char *a);
int strComp(char *a,char *b);
int strCompLim(char*a,char*b,int lim);
void clearScreen();
void clear(char *buffer, int length);
void executeProgram(char* filename,int segment,int *success, char parentIndex);

#endif