#ifndef teks_h
#define teks_h

void printChar(char c);
void printString(char *string);
void readString(char *string);
void readSector(char *buffer, int sector);
void writeSector(char *buffer, int sector);
void printline(char *string);
void copy(char *from, char *to, char *result);

#endif