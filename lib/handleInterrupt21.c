#include "../library.h"

void handleInterrupt21 (int AX, int BX, int CX, int DX) {
    char AL, AH;
    AL = (char) (AX);
    AH = AX >> 8;
  switch (AL) {
    case 0:
      printString(BX);
      break;
    case 1:
      readString(BX);
      break;
    case 2:
      readSector(BX, CX);
      break;
    case 3:
      writeSector(BX, CX);
      break;
    case 4:
      readFile(BX, CX, DX,AH);
      break;
    case 5:
      writeFile(BX, CX, DX,AH);
      break;
    case 6:
      _executeProgram(BX, CX, DX,AH);
      break;
    default:
      printString("Invalid interrupt");
  }

}