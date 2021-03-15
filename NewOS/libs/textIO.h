#if !defined(__TEXTIO_H__)
#define __TEXTIO_H__

void printChar(char c);
void printString(char *string);
void readString(char *string);
void readSector(char *buffer, int sector);
void writeSector(char *buffer, int sector);
void printline(char *string);
void copy(char *from, char *to, char *result);
//void clearScreen();

#endif