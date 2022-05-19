#include "ppm_lib.h"

void compressionManager(FILE *fichier, PPM_IMG* img){
    pixel_structure penultimate_pixel, ultimate_pixel;
    penultimate_pixel.r = 0;
    penultimate_pixel.g = 0;
    penultimate_pixel.b = 0;
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

