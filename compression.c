#include "ppm_lib.h"

void compressionManager(FILE *fichier, PPM_IMG* img){
    pixel_structure penultimate_pixel, ultimate_pixel
                    ,*penultimate_pixelPointer, *ultimate_pixelPointer;
    penultimate_pixel.r = 0;
    penultimate_pixel.g = 0;
    penultimate_pixel.b = 0;
    pixel_structure cache[64]; int index;
    int CIP, *CIP_Pointer = 0;
    int i, j;
    for(i=1;i<=ppmGetHeight(img);i++){
        for(j=1;j<=ppmGetWidth(img);j++){
            write_EVA_BLK_SAME(fichier, penultimate_pixelPointer,ultimate_pixelPointer, CIP_Pointer, cache);
        } 
    }
}

void write_EVA_BLK_SAME(FILE *fichier, pixel_structure *penultimate_pixelPointer, 
                        pixel_structure *ultimate_pixelPointer, int *CIP_Pointer, pixel_structure cache[64]){
    int same;
    same = ComparePixels(penultimate_pixelPointer, ultimate_pixelPointer);
            if(same == 1){
                *CIP_Pointer++;
                //algorithme de SAME
            }
            else  {write_EVA_BLK_INDEX(fichier, penultimate_pixelPointer,ultimate_pixelPointer, cache);}
}

void write_EVA_BLK_INDEX(FILE *fichier, pixel_structure *penultimate_pixelPointer, 
                        pixel_structure *ultimate_pixelPointer, int *CIP_Pointer, pixel_structure cache[64]){
    int index;
    index = (3*(*ultimate_pixelPointer).r + 5*(*ultimate_pixelPointer).g + 7*(*ultimate_pixelPointer).b)%64;
    if(ComparePixels(cache[index], ultimate_pixelPointer)==1){
        fwrite(&index, sizeof(int), 1, fichier);    
    }
    else{
        write_EVA_BLK_DIFF(fichier, penultimate_pixelPointer,ultimate_pixelPointer);
    }
}

void write_EVA_BLK_DIFF(FILE *fichier, pixel_structure *penultimate_pixelPointer, pixel_structure *ultimate_pixelPointer){
    int r_diff, g_diff, b_diff;
    r_diff = (*penultimate_pixelPointer).r - (*ultimate_pixelPointer).r;
    write_EVA_BLK_LUMA(fichier, penultimate_pixelPointer,ultimate_pixelPointer);
}

void write_EVA_BLK_LUMA(FILE *fichier, pixel_structure *penultimate_pixelPointer, pixel_structure *ultimate_pixelPointer){
    write_EVA_BLK_RGB(fichier, penultimate_pixelPointer,ultimate_pixelPointer);
void write_EVA_BLK_INDEX(FILE *fichier, pixel_structure *penultimate_pixelPointer, pixel_structure *ultimate_pixelPointer, pixel_structure cache[64]){
    int index;
    index = (3*(*ultimate_pixelPointer).r + 5*(*ultimate_pixelPointer).g + 7*(*ultimate_pixelPointer).b)%64;
    fwrite(&index, sizeof(int), 1, fichier);

    write_EVA_BLK_DIFF(fichier, penultimate_pixelPointer,ultimate_pixelPointer, cache);
}

void write_EVA_BLK_DIFF(FILE *fichier, pixel_structure *penultimate_pixelPointer, pixel_structure *ultimate_pixelPointer, pixel_structure cache[64]){
    write_EVA_BLK_DIFF(fichier, penultimate_pixelPointer,ultimate_pixelPointer, cache);
}

void write_EVA_BLK_LUMA(FILE *fichier, pixel_structure *penultimate_pixelPointer, pixel_structure *ultimate_pixelPointer){
    write_EVA_BLK_DIFF(fichier, penultimate_pixelPointer,ultimate_pixelPointer, cache);
}

void write_EVA_BLK_RGB(FILE *fichier, pixel_structure *penultimate_pixelPointer, pixel_structure *ultimate_pixelPointer, pixel_structure cache[64]){
    fwrite(0xFE, sizeof(int), 1, fichier);
    fwrite((*ultimate_pixelPointer).r, sizeof(int), 1, fichier);
    fwrite((*ultimate_pixelPointer).g, sizeof(int), 1, fichier);
    fwrite((*ultimate_pixelPointer).b, sizeof(int), 1, fichier);
}

void write_EVA_BLK_DEBUG(FILE *fichier, pixel_structure *penultimate_pixelPointer, pixel_structure *ultimate_pixelPointer, pixel_structure cache[64]){
    fwrite(0xFF, sizeof(int), 1, fichier);
}

void writeHeader(FILE *fichier, PPM_IMG* img){
    int w = ppmGetWidth (img),
        h = ppmGetHeight(img),
        rng = ppmGetColors(img),
        nbColors = ppmGetRange (img);

    fwrite(&w, sizeof(int), 1, fichier);
    fwrite(&h, sizeof(int), 1, fichier);
    fwrite(&rng, sizeof(int), 1, fichier);
    fwrite(&nbColors, sizeof(int), 1, fichier);
} 

