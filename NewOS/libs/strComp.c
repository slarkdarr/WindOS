#include "../library.h"

int strComp(char *a,char* b){
    int i = 0;
    int pja,pjb;
    pja = strlen(a);
    pjb = strlen(b);
    if (pja > pjb) return 0;
    else if (pjb > pja) return 0;
    else {
        for (i = 0; i < pja; i ++){
            if(a[i] != b[i]) return 0;
        }
        return 1;
    }
}