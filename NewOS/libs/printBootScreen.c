#include "../library.h"

void printBootScreen(){
    int pos = 0x8000;
    
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("           ___       _______         ________________ ________          ",pos,0x2);pos+=0xA0;
    printScreen("           __ |     / /___(_)_______ ______  /__  __ \\__  ___/         ",pos,0x2);pos+=0xA0;
    printScreen("           __ | /| / / __  / __  __ \\_  __  / _  / / /_____ \\         ",pos,0x2);pos+=0xA0;
    printScreen("           __ |/ |/ /  _  /  _  / / // /_/ /  / /_/ / ____/ /           ",pos,0x2);pos+=0xA0;
    printScreen("           ____/|__/   /_/   /_/ /_/ \\__,_/   \\____/  /____/          ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    printScreen("                      Please press ENTER to continue...                 ",pos,0xC);pos+=0xA0;
    printScreen("                                                                        ",pos,0x2);pos+=0xA0;
    
    

}