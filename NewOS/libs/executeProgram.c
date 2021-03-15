#include "../library.h"

void executeProgram(char *filename, int segment, int *success, char parentIndex)
{
    interrupt(0x21, (parentIndex << 8) + 0x06, filename, segment, success);
}