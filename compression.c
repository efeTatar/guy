#include "ppm_lib.h"

void compressionManager(pixel_structure *ultimate_pixelPointer, pixel_structure *penultimate_pixelPointer,
                        FILE *fichier, PPM_IMG* img){
    pixel_structure cache[64];
    
    
}

int write_EVA_BLK_SAME(){

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

