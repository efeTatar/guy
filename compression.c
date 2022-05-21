#include "ppm_lib.h"

void compressionManager(FILE *fichier, PPM_IMG* img){
    pixel_structure penultimate, ultimate
                    ,*penultimatePointer, *ultimatePointer;
    penultimate.r = 0;
    penultimate.g = 0;
    penultimate.b = 0;
    penultimatePointer = &penultimate;
    ultimatePointer = &ultimate;
    int dec;
    int test = 0;
    pixel_structure cache[64]; int index;
    char Hex[6] = " ";

    int CIP = 0, *CIP_Pointer = NULL;
    CIP_Pointer = &CIP;
    int i, j;
    writeHeader(fichier, img);
    for(i=0;i<ppmGetHeight(img);i++){
        for(j=0;j<ppmGetWidth(img);j++){
            dec = ppmRead(img, j, i);
            DecimalToHex(Hex, dec);
            HexToRGB(Hex, ultimatePointer);
            write_EVA_BLK_SAME(fichier, penultimatePointer,ultimatePointer, CIP_Pointer, cache);
            test++;
            penultimate = ultimate;
        } 
    }
    printf("%d", test);
}

void write_EVA_BLK_SAME(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    int same;
    same = ComparePixels(penultimatePointer, ultimatePointer);
    if(same == 1){
        *CIP_Pointer++;
        if(*CIP_Pointer==62){*CIP_Pointer +=191; fwrite(*CIP_Pointer, sizeof(int), 1, fichier); *CIP_Pointer = 0;}
        return;
    }
    else{
        if(*CIP_Pointer>0){*CIP_Pointer +=191; fwrite(*CIP_Pointer, sizeof(int), 1, fichier); *CIP_Pointer = 0;}
        write_EVA_BLK_INDEX(fichier, penultimatePointer,ultimatePointer, CIP_Pointer, cache);
    }
}

void write_EVA_BLK_INDEX(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    int index;
    index = (3*(*ultimatePointer).r + 5*(*ultimatePointer).g + 7*(*ultimatePointer).b)%64;
    if(ComparePixels((cache+index), ultimatePointer)==1){
        fwrite(&index, sizeof(int), 1, fichier);    
        return;
    }
    else{
        write_EVA_BLK_DIFF(fichier, penultimatePointer,ultimatePointer, CIP_Pointer, cache);
    }
}

void write_EVA_BLK_DIFF(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    int r_diff, g_diff, b_diff;
    int intervalCheck = 1;
    r_diff = (*penultimatePointer).r - (*ultimatePointer).r;
    g_diff = (*penultimatePointer).g - (*ultimatePointer).g;
    b_diff = (*penultimatePointer).b - (*ultimatePointer).b;
    if(r_diff > 2 || r_diff < -1){intervalCheck = 0;}
    if(g_diff > 2 || g_diff < -1){intervalCheck = 0;}
    if(b_diff > 2 || b_diff < -1){intervalCheck = 0;}
    if(intervalCheck==1){
        r_diff += 2; g_diff += 2; b_diff += 2;
        unsigned int value = 0;
        value += 0x01;
        value = value << 2; 
        value += r_diff;
        value = value << 2; 
        value += g_diff;
        value = value << 2; 
        value += b_diff;
        fwrite(&value, sizeof(unsigned int), 1, fichier);
        return;
    }
    else{
        write_EVA_BLK_LUMA(fichier, penultimatePointer,ultimatePointer, CIP_Pointer, cache);
    }
}

void write_EVA_BLK_LUMA(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    int r_diff, g_diff, b_diff;
    int intervalCheck = 1;
    unsigned int value = 0;
    r_diff = (*penultimatePointer).r - (*ultimatePointer).r;
    g_diff = (*penultimatePointer).g - (*ultimatePointer).g;
    b_diff = (*penultimatePointer).b - (*ultimatePointer).b;
    if(g_diff > 31 || g_diff < -32){intervalCheck = 0;}
    if((r_diff-g_diff) > 7 || (r_diff-g_diff) < -8){intervalCheck = 0;}
    if((b_diff-g_diff) > 7 || (b_diff-g_diff) < -8){intervalCheck = 0;}
    if(intervalCheck==1){
        (value & 0x03) == 0x03;
        value = value << 6;
        (value & 0x3F) == g_diff + 32;
        fwrite(&value, sizeof(unsigned int), 1, fichier);
        value = 0;
        (value & 0xF) == r_diff-g_diff + 8;
        value = value << 4;
        (value & 0xF) == b_diff-g_diff + 8;
        return;
    }
    else{
        write_EVA_BLK_RGB(fichier, penultimatePointer,ultimatePointer, CIP_Pointer, cache);
    }
   
}

void write_EVA_BLK_RGB(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    fwrite("0xFE", sizeof(int), 1, fichier);
    fwrite(&ultimatePointer->r, sizeof(int), 1, fichier);
    fwrite(&ultimatePointer->g, sizeof(int), 1, fichier);
    fwrite(&ultimatePointer->b, sizeof(int), 1, fichier);
}

void write_EVA_BLK_DEBUG(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    fwrite("0xFF", sizeof(int), 1, fichier);
}

void writeHeader(FILE *fichier, PPM_IMG *img){
    int w = ppmGetWidth (img),
        h = ppmGetHeight(img),
        rng = ppmGetColors(img),
        nbColors = ppmGetRange (img);

    fwrite(&w, sizeof(int), 1, fichier);
    fwrite(&h, sizeof(int), 1, fichier);
    fwrite(&rng, sizeof(int), 1, fichier);
    fwrite(&nbColors, sizeof(int), 1, fichier);
}

