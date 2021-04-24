#include "../library.h"

void printBootScreen(){
    int start = 0x8000;
    
    printScreen("                                                                        ",start,0x2);start+=0xA0;
    printScreen("                                                                        ",start,0x2);start+=0xA0;
    printScreen("                                                                        ",start,0x2);start+=0xA0;
    printScreen("                                                                        ",start,0x2);start+=0xA0;
    printScreen("                                                                        ",start,0x2);start+=0xA0;
    printScreen("           ___       _______         ________________ ________          ",start,0x2);start+=0xA0;
    printScreen("           __ |     / /___(_)_______ ______  /__  __ \\__  ___/         ",start,0x2);start+=0xA0;
    printScreen("           __ | /| / / __  / __  __ \\_  __  / _  / / /_____ \\         ",start,0x2);start+=0xA0;
    printScreen("           __ |/ |/ /  _  /  _  / / // /_/ /  / /_/ / ____/ /           ",start,0x2);start+=0xA0;
    printScreen("           ____/|__/   /_/   /_/ /_/ \\__,_/   \\____/  /____/          ",start,0x2);start+=0xA0;
    printScreen("                                                                        ",start,0x2);start+=0xA0;
    printScreen("                                                                        ",start,0x2);start+=0xA0;
    printScreen("                                                                        ",start,0x2);start+=0xA0;
    printScreen("                                                                        ",start,0x2);start+=0xA0;
    printScreen("                                                                        ",start,0x2);start+=0xA0;
    printScreen("                      Please press ENTER to continue...                 ",start,0xC);start+=0xA0;
    printScreen("                                                                        ",start,0x2);start+=0xA0;
    
    

}