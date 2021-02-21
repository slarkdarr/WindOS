void handleInterrupt21 (int AX, int BX, int CX, int DX);
void clearscreen();
void Logo();
void printLogo(char* c,int baris, int kolom, int warna);
void printString(char *string);
void readString(char *string);
void clear(char *buffer, int length);



int main () {
	char* string;

	clearscreen();
    //putInMemory(0xA000, 0x0000+(320*2)+1, 0xD);
    //Logo();
	//printLogo("Hai",0,0,0xE);

    putInMemory(0xB000, 0x8000, 'F');
    putInMemory(0xB000, 0x8001, 0xD);
    
    
    //interrupt(0x10, 0x13, 0, 0, 0);

    
	
	readString(string);

  while (1);
}

void clearscreen(){
  /* Membersihkan layar */
  int i=0;
  for(i=0; i<25; i++)
    printLogo("                                                                                          ",i,0,0x02);
}

void Logo(){
    printLogo("                                        __           ",0,0,0xD);
    printLogo("                 ,-_                  (`  ).         ",1,0,0xD);
    printLogo("                 |-_'-,              (     ).        ",2,0,0xD);
    printLogo("                 |-_'-'           _(        '`.      ",3,0,0xD);
    printLogo("        _        |-_'/        .=(`(      .     )     ",4,0,0xD);
    printLogo("       /;-,_     |-_'        (     (.__.:-`-_.'      ",5,0,0xD);
    printLogo("      /-.-;,-,___|'          `(       ) )            ",6,0,0xD);
    printLogo("     /;-;-;-;_;_/|\\_ _ _ _ _   ` __.:'   )           ",7,0,0xD);
    printLogo("        x_( __`|_P_|`-;-;-;,|        `--'            ",8,0,0xD);
    printLogo("        |\\ \\    _||   `-;-;-'                        ",9,0,0xD);
    printLogo("        | \\   -_|.      '-'                         ",10,0,0xD);
    printLogo("        | /   /-_| `                                 ",11,0,0xD);
    printLogo("        |/   ,'-_|  \\                                ",12,0,0xD);
    printLogo("        /____|'-_|___\\                               ",13,0,0xD);
    printLogo(" _..,____]__|_\\-_'|_[___,.._                         ",14,0,0xD);
    printLogo("'                          ``'--,..,.                ",15,0,0xD);

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
    /* Menulis string*/
	int i =0;
	while (string[i] != '\0'){
		int ch = string[i];
		interrupt(0x10, 0xE*256+ch, 0, 0, 0);
		i++;
	}
}

void readString(char* string){
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
    printString(string);
    
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
