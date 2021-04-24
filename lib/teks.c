#include "teks.h"

void printChar(char c){
    if (c == 0xD){
        interrupt(0x10, 0xE00 + '\r',0,0,0);
        interrupt(0x10, 0xE00 + '\n',0,0,0);
    }
    else if (c == 0xA){
        //
    }
    else{
    interrupt(0x10, 0xE00 + c,0,0,0);
    }
}

void printString(char *string){
    int i = 0;
    while(string[i] != '\0'){
        printChar(string[i]);
        i++;
    }
}

void readString(char *string){
    int  j = 0;
    int max,i;
    char history[512*3];
    int t;
    char curchar,char1;
    readSector(history,0x106);
    readSector(history + 512,0x107);
    readSector(history + 1024, 0x108);


    //cari sektor kosong
    for (;j<=2;j++){
        if (!history[512*j]){
            break;
        }
    }
    max = j;
    i=0;
    while(1){
        t = interrupt(0x16,0,0,0,0);
        curchar = (char) t;
        char1 = (char) (t >> 8);
        if (curchar==0xD) //Enter key
        {
            string[i] = 0x0;
            if (!i) return; //Empty input

            if (max==3){ //Sector penuh
                copy(history+512,history+512*2,history);
                copy(history+512*2,history+512*3,history+512);
                //Last sector
                copy(string,string+512,history+512*2);
    
            }
            else{
                //Sektor tersedia
                copy(string,string+512,history+512* max);
            }
            writeSector(history,0x106);
            writeSector(history+512,0x106 + 1);
            writeSector(history+512*2,0x106 + 2);
            return;
            
        }
        else if (curchar ==0x8){ //Backspace key
            if(i!=0){
                i-=1;
                string[i] = '\0';
                printString("\b \b");
                
            }
        }
        else if (char1 == 0x48 || char1 == 0x50){ //Up key or Down key
            j += char1 == 0x48 ? -1 : 1;
            if (j < 0 || j > max){
                j += char1 == 0x48 ? 1 : -1;
            }
            else{
                if (j == max){
                    string[0] = 0;
                }else{
                    copy(history + j*512, history + (j+1)*512, string);
                }
                while (i--){
                    printString("\b \b");
                }
                i = 0;
                while (string[i])
                {
                    interrupt(0x10, 0xE00 + string[i], 0, 0, 0);
                    i++;
                }
            }
        }
        else{
            string[i] = curchar;
            i+=1;
            printChar(curchar);
        }
    }
}

void readSector(char *buffer, int sector)
{
    interrupt(0x13, 0x201, buffer, div(sector, 36) * 0x100 + mod(sector, 18) + 1, mod(div(sector, 18), 2) * 0x100);
}

void writeSector(char *buffer, int sector)
{
    interrupt(0x13, 0x301, buffer, div(sector, 36) * 0x100 + mod(sector, 18) + 1, mod(div(sector, 18), 2) * 0x100);
}

void printline(char *string){
    printString(string);
    printString("\r\n");    
}

void copy(char *from, char *to, char *result)
{
    int i;
    for (i = 0; i < to - from; i++)
    {
        result[i] = from[i];
    }
    result[i] = 0;
}