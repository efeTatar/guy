#include "ppm_lib.h"

void decompressionManager(FILE *fichier){
    PPM_IMG *img = NULL;
    unsigned int w, h, rng, nbColours;
    freadChar(fichier, &w);
    freadChar(fichier, &h);
    freadChar(fichier, &rng);
    freadChar(fichier, &nbColours);
    img = ppmNew(w, h, rng, nbColours);

    pixel_structure penultimate, ultimate;
    pixel_structure *cache; int index;
    penultimate.r = 0; penultimate.g = 0; penultimate.b = 0;
    cache = malloc(64 * sizeof(pixel_structure));
    int i;
    int x = 0, y = 0;
    int c = 0;
    int a = 1;
    /*for(y=0;y<h;y++){
        for(x=0;x<w;x++){
            printf("(%d %d)", x, y);
            if(c<1){
                type_determiner(fichier, img, &x, &y, &penultimate, &c,
                        &ultimate, cache, w, h);
                ppmWrite(img, x, y, pixel((ultimate).r, (ultimate).g, (ultimate).r));
            }
            else{
                printf("%d", c);
                ppmWrite(img, x, y, pixel((penultimate).r, (penultimate).g, (penultimate).r));
                c--;
            }
            index = (3*(ultimate).r + 5*(ultimate).g + 7*(ultimate).b)%64;
            cache[index] = ultimate;
            penultimate = ultimate;
        }
    }*/
    while(a==1){
            if(c<1){
                type_determiner(fichier, img, &x, &y, &penultimate, &c,
                        &ultimate, cache, w, h);
                printf("(%d %d)(%d %d %d)", x, y, ultimate.r, ultimate.g, ultimate.b);
                ppmWrite(img, x, y, pixel((ultimate).r, (ultimate).g, (ultimate).b));
            }
            else{
                //printf("%d", c);
                ppmWrite(img, x, y, pixel((penultimate).r, (penultimate).g, (penultimate).b));
                c--;
            }
            index = (3*(ultimate).r + 5*(ultimate).g + 7*(ultimate).b)%64;
            cache[index] = ultimate;
            penultimate = ultimate;
            x++;
            if((x)>=w){(x)=0; (y)++;}
            if(y==h){a=0;}
    }
    ppmSave(img, "fml20");
    free(cache);
}

void detected_EVA_BK_SAME(unsigned int byte, PPM_IMG *img, pixel_structure *ultimate, pixel_structure *penultimate, int *i, int *j, int w, int *c){
    ppmWrite(img, *i, *j, pixel((*penultimate).r, (*penultimate).g, (*penultimate).r));
    *c = byte - 191 -1;
    //printf("%d", *c);
}

void detected_EVA_BK_INDEX(unsigned int byte, PPM_IMG *img, pixel_structure *ultimate, pixel_structure cache[64], int *i, int *j){
    int index = byte;
    //printf("index: %d ", index);
    (*ultimate) = cache[index];
    ppmWrite(img, (*i), (*j), pixel((*ultimate).r, (*ultimate).g, (*ultimate).r));
}

void detected_EVA_BK_DIFF(unsigned int byte, PPM_IMG *img, pixel_structure *ultimate, pixel_structure *penultimate, int *i, int *j, pixel_structure cache[64]){
    int diff;
    //printf("diff ");
    unsigned byte2 = 207;
    diff = (byte | byte2) ^ byte2;
    (*ultimate).r = (*penultimate).r - 2 + diff;

    byte2 = 243;
    diff = (byte | byte2) ^ byte2;
    (*ultimate).g = (*penultimate).g - 2 + diff;

    byte2 = 252;
    diff = (byte | byte2) ^ byte2;
    (*ultimate).b = (*penultimate).b - 2 + diff;

    ppmWrite(img, (*i), (*j), pixel((*ultimate).r, (*ultimate).g, (*ultimate).r));
    int index = (3*(*ultimate).r + 5*(*ultimate).g + 7*(*ultimate).b)%64;
    cache[index] = (*ultimate);
}

void detected_EVA_BK_LUMA(FILE *fichier, unsigned int byte, PPM_IMG *img, pixel_structure *ultimate, pixel_structure *penultimate, int *i, int *j, pixel_structure cache[64]){
    unsigned int byte2 = 192;
    int diffg = (byte | byte2) ^ byte2;
    (*ultimate).g = (*penultimate).g - 32 + diffg;
    fread(&byte, sizeof(int), 1, fichier); 
    byte2 = 15;
    int diff;
    diff = (byte | byte2) ^ byte2; diff = diff - 8 + diffg;
    (*ultimate).r = (*penultimate).r + diff;
    byte2 = 240;
    diff = (byte | byte2) ^ byte2; diff = diff - 8 + diffg;
    (*ultimate).b = (*penultimate).b + diff;
    ppmWrite(img, (*i), (*j), pixel((*ultimate).r, (*ultimate).g, (*ultimate).r));
    int index = (3*(*ultimate).r + 5*(*ultimate).g + 7*(*ultimate).b)%64;
    cache[index] = (*ultimate);
}

void detected_EVA_BK_RGB(FILE *fichier, PPM_IMG *img, int *i, int *j, pixel_structure *ultimate, pixel_structure cache[64]){
    unsigned int value;
    freadChar(fichier, &value);
    ultimate->r = value;
    freadChar(fichier, &value);
    ultimate->g = value;
    freadChar(fichier, &value);
    ultimate->b = value;
}

void detected_EVA_BK_DEBUG(){
    return;
}

void type_determiner(FILE *fichier, PPM_IMG *img, int *i, int *j, pixel_structure *penultimatePointeur, int *c,
                    pixel_structure *ultimatePointeur, pixel_structure cache[64], unsigned int w, unsigned int h){
    unsigned int byte;
    freadChar(fichier, &byte);
    switch(byte & 0xC0){
        case 0xC0:
            if(byte == 0xFE){
                detected_EVA_BK_RGB(fichier, img, i, j, ultimatePointeur, cache);
                printf("\nRGB");
                break;
            }                          
            if(byte  == 0xFF ){
                detected_EVA_BK_DEBUG();
                printf("\nDEBUG");
                break;
            }
            else{
                detected_EVA_BK_SAME(byte, img, ultimatePointeur, penultimatePointeur, i, j, w, c);
                printf("\nSAME");
            }
            break;
        case 0x00:
            detected_EVA_BK_INDEX(byte, img, ultimatePointeur, cache, i, j);
            printf("\nINDEX");
            break;
        case 0x40:
            detected_EVA_BK_DIFF(byte, img, ultimatePointeur, penultimatePointeur, i, j, cache);
            printf("\nDIFF");
            break;
        case 0x80:
            detected_EVA_BK_LUMA(fichier, byte, img, ultimatePointeur, penultimatePointeur, i, j, cache);
            printf("\nLUMA");
            if((*i)>=w){(*i)=0; (*j)++; printf("a");}
            freadChar(fichier, &byte);
            break;
    }
}
