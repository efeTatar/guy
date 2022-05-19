#include "ppm_lib.h"

void compressionManager(FILE *fichier, PPM_IMG* img){
    pixel_structure penultimate_pixel, ultimate_pixel
                    ,*penultimate_pixelPointer, *ultimate_pixelPointer;
    penultimate_pixel.r = 0;
    penultimate_pixel.g = 0;
    penultimate_pixel.b = 0;
    pixel_structure cache[64];
    int CIP, *CIP_pointer = 0;
    int i, j;
    for(i=1;i<=ppmGetHeight(img);i++){
        for(j=1;j<=ppmGetWidth(img);j++){
            write_EVA_BLK_SAME(penultimate_pixelPointer,ultimate_pixelPointer);
        } 
    }
}

void write_EVA_BLK_SAME(pixel_structure *penultimate_pixelPointer, pixel_structure *ultimate_pixelPointer, int *CIP_Pointer){
    int same;
    same = ComparePixels(penultimate_pixelPointer, ultimate_pixelPointer);
            if(same == 1){
                *CIP_Pointer++;
                //algorithme de SAME
            }
            else  {write_EVA_BLK_INDEX(penultimate_pixelPointer,ultimate_pixelPointer);}
}

void write_EVA_BLK_INDEX(pixel_structure *penultimate_pixelPointer, pixel_structure *ultimate_pixelPointer){

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

