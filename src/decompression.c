#include "ppm_lib.h"

void decompressionManager(FILE *fichier){
    rewind(fichier);
    PPM_IMG *img = NULL;
    unsigned int w, h, rng, nbColours;
    fread(&w, sizeof(unsigned int), 1, fichier);
    fread(&h, sizeof(unsigned int), 1, fichier);
    freadChar(fichier, &rng);
    freadChar(fichier, &nbColours);
    img = ppmNew(w, h, rng, nbColours);
    //printf("%d %d", ppmGetWidth(img), ppmGetHeight(img));

    pixel_structure penultimate, ultimate;
    pixel_structure *cache; int index;
    penultimate.r = 0; penultimate.g = 0; penultimate.b = 0;
    cache = malloc(64 * sizeof(pixel_structure));
    int i;
    int x = 0, y = 0;
    int c = 0;
    int a = 1;
    while(a==1){
            if(c>0){
                ppmWrite(img, x, y, pixel((penultimate).r, (penultimate).g, (penultimate).b));
                c--;
            }
            else{
                type_determiner(fichier, img, &x, &y, &penultimate, &c,
                        &ultimate, cache, w, h);
                //printf("(%d %d)(%d %d %d)", x, y, ultimate.r, ultimate.g, ultimate.b);
                ppmWrite(img, x, y, pixel((ultimate).r, (ultimate).g, (ultimate).b));
            }
            index = (3*(ultimate).r + 5*(ultimate).g + 7*(ultimate).b)%64;
            cache[index] = ultimate;
            penultimate = ultimate;
            x++;
            if((x)>=w){(x)=0; (y)++;}
            if(y==h){a=0;}
    }
    ppmSave(img, "decompressedImage");
    free(cache);
}

void detected_EVA_BK_SAME(unsigned int byte, PPM_IMG *img, pixel_structure *ultimate, pixel_structure *penultimate, int *i, int *j, int w, int *c){
    ppmWrite(img, *i, *j, pixel((*penultimate).r, (*penultimate).g, (*penultimate).r));
    *c = byte - 191 -1;
    //printf("%d ", *c+1);
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
    diff = (byte & 48) >> 4;
    (*ultimate).r = (*penultimate).r - 2 + diff;

    diff = (byte & 12) >> 2;
    (*ultimate).g = (*penultimate).g - 2 + diff;

    diff = (byte & 3);
    (*ultimate).b = (*penultimate).b - 2 + diff;

    ppmWrite(img, (*i), (*j), pixel((*ultimate).r, (*ultimate).g, (*ultimate).r));
    int index = (3*(*ultimate).r + 5*(*ultimate).g + 7*(*ultimate).b)%64;
    cache[index] = (*ultimate);
}

void detected_EVA_BK_LUMA(FILE *fichier, unsigned int byte, PPM_IMG *img, pixel_structure *ultimate, pixel_structure *penultimate, int *i, int *j, pixel_structure cache[64]){
    byte -= 128;
    unsigned int gDiff, rDiff, bDiff;
    gDiff = byte - 32;
    (*ultimate).g = gDiff + (*penultimate).g;
    freadChar(fichier, &byte);
    rDiff = ((byte & 0xF0)>>4)+ gDiff - 8;
    (*ultimate).r = rDiff + (*penultimate).r;
    bDiff = (byte & 0xF) + gDiff - 8;
    (*ultimate).b = bDiff + (*penultimate).b;
    //printf("(%d %d %d)", (*ultimate).r, (*ultimate).g, (*ultimate).b);
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
                //printf("\nRGB");
                break;
            }                          
            if(byte  == 0xFF ){
                detected_EVA_BK_DEBUG();
                //printf("\nDEBUG");
                break;
            }
            else{
                detected_EVA_BK_SAME(byte, img, ultimatePointeur, penultimatePointeur, i, j, w, c);
                //printf("\nSAME");
            }
            break;
        case 0x00:
            detected_EVA_BK_INDEX(byte, img, ultimatePointeur, cache, i, j);
            //printf("\nINDEX");
            break;
        case 0x40:
            detected_EVA_BK_DIFF(byte, img, ultimatePointeur, penultimatePointeur, i, j, cache);
            //printf("\nDIFF");
            break;
        case 0x80:
            detected_EVA_BK_LUMA(fichier, byte, img, ultimatePointeur, penultimatePointeur, i, j, cache);
            //printf("\nLUMA");
            break;
    }
}
