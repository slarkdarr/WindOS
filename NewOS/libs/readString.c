#include "../library.h"

void readString(char *string){
    int  j = 0;
    int max,i;
    char history[512*3];
    int tes;
    char curchar,char1;
    readSector(history,0x106);
    readSector(history + 512,0x107);
    readSector(history + 1024, 0x108);


    //ini nyari sektor yang kosong
    for (;j<=2;j++){
        if (!history[512*j]){
            break;
        }
    }
    max = j;
    i=0;
    while(1){
        tes = interrupt(0x16,0,0,0,0);
        curchar = (char) tes;
        char1 = (char) (tes >> 8);
        if (curchar==0xD) //0xD = ENTER
        {
            string[i] = 0x0;
            if (!i) return;//kalau dia itu stringnya cuma enter

            if (max==3){//kalau sector full
                //geser semua sektor
                copy(history+512,history+512*2,history);
                copy(history+512*2,history+512*3,history+512);
                //isi sektor terakhir
                copy(string,string+512,history+512*2);
    
            }
            else{
                //langsung tambahin di sektor yang tersedia
                copy(string,string+512,history+512* max);
            }
            writeSector(history,0x106);
            writeSector(history+512,0x106 + 1);
            writeSector(history+512*2,0x106 + 2);
            return;
            
        }
        else if (curchar ==0x8){ // 0x8 = backspace
            if(i!=0){
                i-=1;
                string[i] = '\0';
                printString("\b \b");
                
            }
        }
        else if (char1 == 0x48 || char1 == 0x50){ // up down
            // printString("up/down");
            j += char1 == 0x48 ? -1 : 1;
            if (j < 0 || j > max){
                j += char1 == 0x48 ? 1 : -1;
            }
            else{
                if (j == max){
                    string[0] = 0;
                }else{
                    copy(history + j*512, history + (j+1)*512, string);
                    // printString("this :");
                    // printline(string);
                }
                while (i--){
                    printString("\b \b");
                }
                i = 0;
                while (string[i])
                {
                    interrupt(0x10, 0xE00 + string[i], 0, 0, 0); // printChar string[i]
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