#include "../library.h"

void defaultDir(){
    char cD[512];
    clear(cD,512);
    writeSector(cD,0x104);
}