#include "ppm_lib.h"

// Manages the compression process
void compressionManager(FILE *fichier, PPM_IMG* img){

    // Creates puniltimate and ultimate pixel structures;
    pixel_structure penultimate, ultimate;

    // Sets initial penultimate pixel values to 0
    penultimate.r = 0;
    penultimate.g = 0;
    penultimate.b = 0;

    pixel_structure *cache; int index;
    cache = malloc(64 * sizeof(pixel_structure));

    // Creates Hexadecimal string to convert decimal values to pixel structure
    char Hex[6];

    // Number of Consecutive Indentical Pixels
    int CIP = 0;

    // Copies header into compression file
    writeHeader(fichier, img);

    // Copies body into compression file
    int x, y;
    for(y=0;y<ppmGetHeight(img);y++){
        for(x=0;x<ppmGetWidth(img);x++){

            // Conversion of decimal value returned by provided functions
            DecimalToHex(Hex, ppmRead(img, x, y));
            HexToRGB(Hex, &ultimate);
            
            // Start of loop
            check_EVA_BLK_SAME(fichier, &penultimate, &ultimate, &CIP, cache);

            // Resets penultimate pixel values
            penultimate = ultimate;

            // Puts ultimate pixel into cache
            index = (3*ultimate.r + 5*ultimate.g + 7*ultimate.b)%64;
            cache[index] = ultimate;

            // Writes number of consecutive identical pixels and nullifies it
            if(CIP==62){
                CIP+=191;
                fwrite(&CIP, sizeof(unsigned char), 1, fichier);
                CIP = 0;
            }
        }
    }
    // Writes the number of consecutive identical pixels if it stays unwritten
    if(CIP>0){
        CIP+=191;
        fwrite(&CIP, sizeof(unsigned char), 1, fichier);
        CIP = 0;
    }

    check_EVA_BLK_DEBUG(fichier, &penultimate, &ultimate, &CIP, cache);
    free(cache);
}

// Functions decide what pixel block to write
// Each one checks if they are supposed to write their corresponding blocks

void check_EVA_BLK_SAME(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    
    // Checks if the ultimate pixel is identical to the penultimate one
    if(ComparePixels(penultimatePointer, ultimatePointer)==1){
        (*CIP_Pointer)++;
        return;
    }
    else{
        // Writes the number of consecutive identical pixels an nullifies it
        if(*CIP_Pointer>0){
            *CIP_Pointer += 191;
            fwrite(CIP_Pointer, sizeof(unsigned char), 1, fichier);
            *CIP_Pointer = 0;
        }
        // Continuity of loop
        check_EVA_BLK_INDEX(fichier, penultimatePointer,ultimatePointer, CIP_Pointer, cache);
    }
}

void check_EVA_BLK_INDEX(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    // Computes index for ultimate pixel
    int index;
    index = (3*(*ultimatePointer).r + 5*(*ultimatePointer).g + 7*(*ultimatePointer).b)%64;

    // Checks if the ultimate pixel is identical to the one in the cache
    // Writes the value of index if so
    if(ComparePixels((cache+index), ultimatePointer)==1){
        fwrite(&index, sizeof(unsigned char), 1, fichier);
        return;
    }
    else{
        // Continuity of loop
        check_EVA_BLK_DIFF(fichier, penultimatePointer,ultimatePointer, CIP_Pointer, cache);
    }
}

void check_EVA_BLK_DIFF(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    
    // The purpose of this variable is to check if EVLA BLK SAME values are in range
    // It is set to 0 if not
    int check = 1;
    int rdiff = (*ultimatePointer).r-(*penultimatePointer).r, 
        gdiff = (*ultimatePointer).g-(*penultimatePointer).g,
        bdiff = (*ultimatePointer).b-(*penultimatePointer).b;
    if(rdiff>1 || rdiff<-2){check=0;}
    if(gdiff>1 || gdiff<-2){check=0;}
    if(bdiff>1 || bdiff<-2){check=0;}

    //Writes EVA BLK DIFF values in a single byte
    if(check==1){
        
        // The algorithm requires adding 2 before storing values
        rdiff += 2;
        gdiff += 2;
        bdiff += 2;

        // Creates byte to stock EVA BLK DIFF values
        unsigned int byte = 0;

        // EVA BLK DIFF block is in the format 01 XX XX XX
        // Each bit is pushed by 2 bits to the left in order to achieve this
        byte = 1; byte = byte << 2;
        byte = byte | rdiff;
        byte = byte << 2;
        byte = byte | gdiff;
        byte = byte << 2;
        byte = byte | bdiff;
        fwrite(&byte, sizeof(unsigned char), 1, fichier);
        return;
    }
    // Continuity of loop
    check_EVA_BLK_LUMA(fichier, penultimatePointer,ultimatePointer, CIP_Pointer, cache);
}

void check_EVA_BLK_LUMA(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    
    // Computes the difference between the penultimate pixel and the ultimate one
    int rdiff = (*ultimatePointer).r-(*penultimatePointer).r, 
        gdiff = (*ultimatePointer).g-(*penultimatePointer).g,
        bdiff = (*ultimatePointer).b-(*penultimatePointer).b;

    // check variable is initialised
    int check = 1;

    // Function checks if the difference stays in given intervals, nullifies check if not
    if(gdiff>31 || gdiff<-32){check=0;}
    int rgdiff = rdiff - gdiff, bgdiff = bdiff - gdiff;
    if(rgdiff>7 || rgdiff<-8){check=0;}
    if(bgdiff>7 || bgdiff<-8){check=0;}

    // if check is equal to 1, the function writes the LUMA block
    if(check==1){
        
        // First byte is created with corresponding first 2 bits 
        unsigned int byte = 0;
        byte = 2;
        byte = byte << 6;
        gdiff += 32;
        //6 bits store the difference between ultimate and penultimate green values
        byte = byte | gdiff;
        fwrite(&byte, sizeof(unsigned char), 1, fichier);

        // Second byte is being created storing difference betwenn ultimate and penultimate red and blue values
        byte = 0;
        rgdiff += 8;
        bgdiff += 8;
        byte = byte | rgdiff;
        byte = byte << 4;
        byte = byte | bgdiff;
        fwrite(&byte, sizeof(unsigned char), 1, fichier);
        return;
    }
    // Continuity of loop
    check_EVA_BLK_RGB(fichier, penultimatePointer,ultimatePointer, CIP_Pointer, cache);
}

void check_EVA_BLK_RGB(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    
    // If none of the functions was valid, the function writes the ultimate RGB values
    unsigned int byte = 0xFE;
    fwrite(&byte, sizeof(unsigned char), 1, fichier);
    fwrite(&(ultimatePointer->r), sizeof(unsigned char), 1, fichier);
    fwrite(&(ultimatePointer->g), sizeof(unsigned char), 1, fichier);
    fwrite(&(ultimatePointer->b), sizeof(unsigned char), 1, fichier);
    // End of loop
}

void check_EVA_BLK_DEBUG(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    // The debug block is only used if the devs see it fit
    unsigned int byte;
    byte = 0xFF;
    fwrite(&byte, sizeof(unsigned char), 1, fichier);
}

// Copies header into compression file
// w: width
// h: height 
// rng: range of colours
// nbColors: number of colours
void writeHeader(FILE *fichier, PPM_IMG *img){
    unsigned int w = ppmGetWidth(img),
        h = ppmGetHeight(img),
        rng = ppmGetRange(img),
        nbColors = ppmGetColors(img);
    fwrite(&w, sizeof(unsigned int), 1, fichier);
    fwrite(&h, sizeof(unsigned int), 1, fichier);
    fwrite(&rng, sizeof(unsigned char), 1, fichier);
    fwrite(&nbColors, sizeof(unsigned char), 1, fichier);
}

