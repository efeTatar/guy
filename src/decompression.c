#include "ppm_lib.h"

// Manages the decompression precess
void decompressionManager(FILE *fichier){
    rewind(fichier);
    // Creates new pointer and variables for the image
    PPM_IMG *img = NULL;
    // width, height, rang, number of colours
    unsigned int w, h, rng, nbColours;
    // Tjhe function extracts values from bytes and creates new image
    fread(&w, sizeof(unsigned int), 1, fichier);
    fread(&h, sizeof(unsigned int), 1, fichier);
    freadChar(fichier, &rng);
    freadChar(fichier, &nbColours);
    img = ppmNew(w, h, rng, nbColours);

    // Ultimate and Penultiate pixels are created
    pixel_structure penultimate, ultimate;
    // The cache and the index are created
    pixel_structure *cache; int index;
    // penultimate pixel values are set to 0
    penultimate.r = 0; penultimate.g = 0; penultimate.b = 0;
    cache = malloc(64 * sizeof(pixel_structure));
    int i;
    int x = 0, y = 0;
    // c keeps track of how many identicals pixels to put consecutively
    int c = 0;
    // a is set to 0 when the image is fully built to stop the loop
    int a = 1;

    // The user can render the image in black and white
    printf("Would you like to render your image black and white?");
    // bnw (black and white) is set to a user input 
    // setting bnw to 1 will render the image black and white
    int bnw = 0;
    scanf("%d", &bnw);
    // greyscale is the variable used to compute grey values if the image is to be rendered in black and white
    int greyscale;

    //
    while(a==1){
            if(c>0){
                if(bnw==1){
                    greyscale = 0.3 * (penultimate).r + 0.59 * (penultimate).g + 0.11 * (penultimate).b;
                    ppmWrite(img, x, y, pixel(greyscale, greyscale, greyscale));
                }
                else{
                    ppmWrite(img, x, y, pixel((penultimate).r, (penultimate).g, (penultimate).b));
                }
                c--;
            }
            else{
                type_determiner(fichier, img, &x, &y, &penultimate, &c,
                        &ultimate, cache, w, h);
                if(bnw==1){
                    greyscale = 0.3 * (ultimate).r + 0.59 * (ultimate).g + 0.11 * (ultimate).b;
                    ppmWrite(img, x, y, pixel(greyscale, greyscale, greyscale));
                }
                else{
                    ppmWrite(img, x, y, pixel((ultimate).r, (ultimate).g, (ultimate).b));
                }
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

// Interprets EVA BK SAME block
void detected_EVA_BK_SAME(unsigned int byte, PPM_IMG *img, pixel_structure *ultimate, pixel_structure *penultimate, int *i, int *j, int w, int *c){
    // Extracts the number of consecutive identical pixels and places the first one
    ppmWrite(img, *i, *j, pixel((*penultimate).r, (*penultimate).g, (*penultimate).r));
    *c = byte - 191 -1;
}

// Interprets EVA BK INDEX block
void detected_EVA_BK_INDEX(unsigned int byte, PPM_IMG *img, pixel_structure *ultimate, pixel_structure cache[64], int *i, int *j){
    // Extracts index value from byte and sets ultimate pixel to the corresponding pixel in the cache
    int index = byte;
    (*ultimate) = cache[index];
}

// Interprets EVA BK DIFF block
void detected_EVA_BK_DIFF(unsigned int byte, PPM_IMG *img, pixel_structure *ultimate, pixel_structure *penultimate, int *i, int *j, pixel_structure cache[64]){
    int diff;

    // Computes difference between ultimate and penultimate red values by extracting corresponding two bits
    diff = (byte & 48) >> 4;
    // Sets ultimate red value
    (*ultimate).r = (*penultimate).r - 2 + diff;

    // Computes difference between ultimate and penultimate green values by extracting corresponding two bits
    diff = (byte & 12) >> 2;
    // Sets ultimate green value
    (*ultimate).g = (*penultimate).g - 2 + diff;

    // Computes difference between ultimate and penultimate blue values by extracting corresponding two bits
    diff = (byte & 3);
    // Sets ultimate blue value
    (*ultimate).b = (*penultimate).b - 2 + diff;
}

// Interprets EVA BK LUMA block
void detected_EVA_BK_LUMA(FILE *fichier, unsigned int byte, PPM_IMG *img, pixel_structure *ultimate, pixel_structure *penultimate, int *i, int *j, pixel_structure cache[64]){
    unsigned int gDiff, rDiff, bDiff;
    
    // Removes first two indicator bits from the first byte
    byte -= 128;
    // Extracts difference between ultimate and penultimate green values from first byte
    gDiff = byte - 32;
    (*ultimate).g = gDiff + (*penultimate).g;

    // Reads second LUMA byte
    freadChar(fichier, &byte);
    // Extracts differences between ultimate and penultimate values and uses them to set new values
    rDiff = ((byte & 0xF0)>>4)+ gDiff - 8;
    (*ultimate).r = rDiff + (*penultimate).r;
    bDiff = (byte & 0xF) + gDiff - 8;
    (*ultimate).b = bDiff + (*penultimate).b;
}

// Interprets EVA BK RGB block
void detected_EVA_BK_RGB(FILE *fichier, PPM_IMG *img, int *i, int *j, pixel_structure *ultimate, pixel_structure cache[64]){
    unsigned int value;
    // Extracts RGB values by reading 3 bytes and sets ultimate RGB values
    freadChar(fichier, &value);
    ultimate->r = value;
    freadChar(fichier, &value);
    ultimate->g = value;
    freadChar(fichier, &value);
    ultimate->b = value;
}

// Interprets EVA BK DEBUG block
void detected_EVA_BK_DEBUG(){
    return;
}

// Determines block type of byte and calls respective function
void type_determiner(FILE *fichier, PPM_IMG *img, int *i, int *j, pixel_structure *penultimatePointeur, int *c,
                    pixel_structure *ultimatePointeur, pixel_structure cache[64], unsigned int w, unsigned int h){
    unsigned int byte;
    freadChar(fichier, &byte);
    // Checks first two bits (indicator) to determine block type
    switch(byte & 0xC0){
        case 0xC0:
            if(byte == 0xFE){
                detected_EVA_BK_RGB(fichier, img, i, j, ultimatePointeur, cache);
                break;
            }                          
            if(byte  == 0xFF ){
                detected_EVA_BK_DEBUG();
                break;
            }
            else{
                detected_EVA_BK_SAME(byte, img, ultimatePointeur, penultimatePointeur, i, j, w, c);
            }
            break;
        case 0x00:
            detected_EVA_BK_INDEX(byte, img, ultimatePointeur, cache, i, j);
            break;
        case 0x40:
            detected_EVA_BK_DIFF(byte, img, ultimatePointeur, penultimatePointeur, i, j, cache);
            break;
        case 0x80:
            detected_EVA_BK_LUMA(fichier, byte, img, ultimatePointeur, penultimatePointeur, i, j, cache);
            break;
    }
}
