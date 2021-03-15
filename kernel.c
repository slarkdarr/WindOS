void handleInterrupt21 (int AX, int BX, int CX, int DX);
void clearscreen();
void printBlock();
void printLogo(char* c,int baris, int kolom, int warna);
void printString(char *string);
void printString2(char *string, int baris, int kolom);
void readString(char *string);
void clear(char *buffer, int length);


int main () {
	char* string;

    printLogo("Hai", 5,5,0xD);

    handleInterrupt21(3, 0, 0, 0);
    readString(string);
    clear(0xA0000, 4098); // ini harusnya ngeclear buffernya

 //    interrupt(0x10, 0x3, 0,0,0); // ga terjadi apa2
 //    clearscreen();
	// printLogo("Hai",5,5,0xD); //ga keprint
 //    printString("Test"); //ga keprint
	
	// readString(string);

 //    printLogo("Hai",5,5,0xD);

 //    putInMemory(0xB000, 320+0x8000, 'H');
	// putInMemory(0xB000, 320+0x8001, 0xC);

 //    printString2("Test lagi", 3, 0);

  while (1);
}

void clearscreen(){
  /* Membersihkan tulisan x86 blablabla dari layar */
  int i=0;
  for(i=0; i<25; i++)
    printLogo("                                                                                          ",i,0,0x02);
}


void printLogo(char* c,int baris, int kolom, int warna){
	/* Menulis string pada baris dan kolom dengan warna sesuai parameter fungsi */
    int i, b, alamat;
	i = 0;

	alamat = (baris)*80*2 + 2*kolom;
	while(c[i] != '\0'){
		b = alamat;
		putInMemory(0xB000, b+0x8000, c[i]);
		putInMemory(0xB000, b+0x8001, warna);
		i = i + 1;
		alamat = alamat + 2;
	}

}

void printString(char* string){
	int i =0;
	while (string[i] != '\0'){
		int ch = string[i];
		interrupt(0x10, 0xE*256+ch, 0, 0, 0);
		i++;
	}
}


void readString(char* string){
    // char* testVar = ['s', 'h', 'i', 'f', 'a'];
    int dashn = 0xa;	// \n character new line biasa
    int endStr = 0x0; 	// blank
    int dashr = 0xd;	// 
    char backspace[4];	// set of command buat backspace
    char CC = '\0';
    int i = 0;

    char enter[3];		// set of commands buat enter
    enter[0] = '\r';
    enter[1] = '\n';
    enter[2] = '\0';

    
    backspace[0] = '\b';
    backspace[1] =  ' ';
    backspace[2] = '\b';
    backspace[3] = '\0';
    
    

    while (CC != '\r'){
    	CC = interrupt(0x16, 0x0, 0x0, 0x0, 0x0);

    	switch(CC){
    		case '\0':
    			break;
    		case '\b' :
    			if (i>0){
    				i--;
    				string[i]= '\0';
    				printString(backspace);
    			}
    			break;
    		case '\r':
    			break;
    		default:
    			string[i] = CC;
    			i++;
    			interrupt(0x10, 0xE*256+CC, 0, 0, 0);
    				
    	}
    }
    string[i] = '\0';
    printString(enter);
    printLogo(string, 1, 0, 0xE);

    // printLogo(testVar, 5, 0, 0xC);
    
}

void handleInterrupt21 (int AX, int BX, int CX, int DX){	
    switch (AX) {
        case 0:
            printString(BX);
            break;
        case 1:
            readString(BX);
            break;
        case 3:
            printBlock();
            break;
        default:
            printString("Invalid interrupt");
    }

        
}

void printBlock() {
    extern char imageFile;
	char* image = &imageFile;
    int xOffset, yOffset;
    int i, j;
	int h;
	//int address;

    interrupt(0x10, 0x13, 0, 0, 0);
	xOffset = 100;
	yOffset = 0;
	h = 2;
    for (i=0; i<image[0]; i++) {
        for (j=0; j<image[1]; j++) {
            putInMemory(0xA000, 0x0000+(320*(j+yOffset))+i+xOffset, image[h]);
			h++;
        }
    }

}

void clear(char* buff, int len){
	int i;
	for(i=0;i<len;i++){
		buff[i] = 0x0;
	}
}