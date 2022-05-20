#include "ppm_lib.h"

void decompressionManager(FILE *fichier){
    PPM_IMG* img = NULL;
    int w, h, rng, nbColours;
    fread(&w, sizeof(int), 1, fichier);
    fread(&h, sizeof(int), 1, fichier);
    fread(&rng, sizeof(int), 1, fichier);
    fread(&nbColours, sizeof(int), 1, fichier);
    img = ppmNew(w, h, rng, nbColours);

    pixel_structure penultimate, ultimate;
    pixel_structure cache[64]; int index;
    penultimate.r = 0;
    penultimate.g = 0;
    penultimate.b = 0;

    int i, j;
    for(i=0;i<h;i++){
        for(j=0;j<w;j++){

            penultimate = ultimate;
        }
    }
    
}

void detecter_EVA_BK_RGB();

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
