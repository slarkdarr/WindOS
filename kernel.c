void handleInterrupt21 (int AX, int BX, int CX, int DX);
void printString(char *string);
void readString(char *string);
void clear(char *buffer, int length);

int main () {
  putInMemory(0xB000, 0x8000, 'H');
  putInMemory(0xB000, 0x8001, 0xD);
  putInMemory(0xB000, 0x8002, 'a');
  putInMemory(0xB000, 0x8003, 0xD);
  putInMemory(0xB000, 0x8004, 'i');
  putInMemory(0xB000, 0x8005, 0xD);

  while (1);
}

void clear(char* buffer, int length){
	int i;
	for(i=0;i<length;i++){
		buffer[i] = 0x0;
	}
}

void printString(char* chars){

   
    int i = 0;
    while(chars[i] != '\0'){
            int ch = chars[i];
            /* interrupt #, AX, BX, CX, DX */
		        interrupt(0x10, 0xe*256+ch, 0, 0, 0);
            i++;
    }


}

void readString(char* buff){
    int dashn = 0xa;
    int endStr = 0x0;
    int enter = 0xd;
    int backsp = 0x8;
    int dashr = 0xd;
    int loop = 1;
    int count = 2;
    buff[0] = dashr;
    buff[1] = dashn;
    while(loop){
            /* Call interrupt 0x16 */
            /* interrupt #, AX, BX, CX, DX */
            int ascii = interrupt(0x16,0,0,0,0);
            if (ascii == enter){              
				buff[count] = 0x0;
                buff[count+1] = dashr;
                buff[count+2] = dashn;
                return;
            }
            else if (ascii == backsp){
                if (count > 1){
                    buff[count] = 0x0;
                    count--;
                    interrupt(0x10,0xe*256+0x8,0,0,0);
                    count++;
                    interrupt(0x10,0xe*256+0x0,0,0,0);
                    count--;
                    interrupt(0x10,0xe*256+0x8,0,0,0);
                    
               }
            }
            else{
                buff[count] = ascii;
                interrupt(0x10, 0xe*256+ascii, 0, 0, 0);
                count++;
            }     
    }
}

void handleInterrupt21 (int AX, int BX, int CX, int DX){	
        switch (AX) {
        	case 0:
        		printString(BX);
        		break;
        	case 1:
        		readString(BX);
        		break;
        	default:
        		printString("Invalid interrupt");
        }

        
}
