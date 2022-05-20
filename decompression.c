#include "ppm_lib.h"

void decompressionManager(FILE *fichier){
    PPM_IMG* img = NULL;
}



//NATHAN LE DIEU 
//EFE LE NULOS


int direction(FILE *ficher){
    int value;
    switch(value & 0xC0){
        case 0xC0:
            //fct SAME;
            break;
        case 0x00:
            //fct INDEX
            break;
        case 0x40:
            //fct DIFF
            break;
        case 0x80:
            //fct LUMA
            break;
        default: 
            //Fct RGB avec verif de DEBUG
            break;
    }
}
