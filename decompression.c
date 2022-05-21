#include "ppm_lib.h"

void decompressionManager(FILE *fichier){
    PPM_IMG *img = NULL;
    int w, h, rng, nbColours;
    fread(&w, sizeof(int), 1, fichier);
    fread(&h, sizeof(int), 1, fichier);
    fread(&rng, sizeof(int), 1, fichier);
    fread(&nbColours, sizeof(int), 1, fichier);
    img = ppmNew(w, h, rng, nbColours);

    pixel_structure penultimate, ultimate;
    pixel_structure penultimatePointeur, ultimatePointeur;
    pixel_structure *cache; int index;
    cache = malloc(64 * sizeof(pixel_structure));
    penultimate.r = 0;
    penultimate.g = 0;
    penultimate.b = 0;

    int debugCount = 0;

    // i->y & j->x 
    int i, j;

    while(debugCount<10){ 
        type_determiner();
    }

    free(cache);
}

void detected_EVA_BK_SAME(unsigned int byte, PPM_IMG *img, pixel_structure *ultimate, pixel_structure *penultimate, int *i, int *j, int w){
    int repeat; 
    repeat = byte;
    while(repeat!=0){
        ppmWrite(img, (*i), (*j), pixel((*penultimate).r, (*penultimate).g, (*penultimate).r));
        (*i)++;
        if((*i)=w){(*i)=0;(*j)++;}       
    }
}

void detected_EVA_BK_INDEX(unsigned int byte, PPM_IMG *img, pixel_structure *ultimate, pixel_structure cache[64], int *i, int *j){
    int index = byte;
    (*ultimate) = cache[index];
    ppmWrite(img, (*i), (*j), pixel((*ultimate).r, (*ultimate).g, (*ultimate).r));
    (*i)++;
}

void detected_EVA_BK_DIFF(unsigned int byte, PPM_IMG *img, pixel_structure *ultimate, pixel_structure *penultimate, int *i, int *j){
    int diff;
    unsigned int byte2;
    byte2 = byte;
    byte2 = byte2 << 2;
    diff = byte2 >> 6;
    (*ultimate).r = (*penultimate).r - 2 + diff;
    byte2 = byte;
    byte2 = byte2 << 4;
    diff = byte2 >> 6;
    (*ultimate).g = (*penultimate).g - 2 + diff;
    byte2 = byte;
    byte2 = byte2 << 6;
    diff = byte2 >> 6;
    (*ultimate).b = (*penultimate).b - 2 + diff;
    ppmWrite(img, (*i), (*j), pixel((*ultimate).r, (*ultimate).g, (*ultimate).r));
    (*i)++;
}

void detected_EVA_BK_LUMA(){
    
}

void detected_EVA_BK_RGB(FILE *fichier, PPM_IMG *img, int *i, int *j, pixel_structure *ultimate){
    fread(&(*ultimate).r, sizeof(int), 1, fichier);
    fread(&(*ultimate).g, sizeof(int), 1, fichier);
    fread(&(*ultimate).b, sizeof(int), 1, fichier);
    ppmWrite(img, (*i), (*j), pixel((*ultimate).r, (*ultimate).g, (*ultimate).r));
    (*i)++;
}

void detected_EVA_BK_DEBUG(){
    //
}

void type_determiner(FILE *fichier, PPM_IMG *img, int *i, int *j, pixel_structure penultimatePointeur, 
                    pixel_structure ultimatePointeur, pixel_structure cache[64], int w, int h){
    unsigned int byte, check_byte;
    fread(&byte, sizeof(int), 1, fichier);
    check_byte = byte >> 6;
    switch(check_byte){
        case 0x3:
            if( (byte & 0xFE) == 0xFE ){
                //RGB
                if((*i)=w){(*i)=0;(*j)++;}
                break;
            }
            if( (byte & 0xFF) == 0xFF ){
                //DEBUG
                break;
            }
            //SAME
            break;

        case 0x0:
            //INDEX
            if((*i)=w){(*i)=0;(*j)++;}
            break;

        case 0x1:
            //DIFF
            if((*i)=w){(*i)=0;(*j)++;}
            break;

        case 0x2:
            //LUMA
            break;
    }
}
