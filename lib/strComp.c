#include "../library.h"

int strComp(char *a,char* b){
    int i = 0;
    int nA,nB;
    nA = strlen(a);
    nB = strlen(b);
    if (nA > nB) return 0;
    else if (nB > nA) return 0;
    else {
        for (i = 0; i < nA; i ++){
            if(a[i] != b[i]) return 0;
        }
        return 1;
    }
}