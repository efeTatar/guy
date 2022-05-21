#include "ppm_lib.h"

int main(){

    pixel_structure penultimate_pixel, ultimate_pixel, 
        *penultimate_pixelPointer, *ultimate_pixelPointer;  

    //sets the initial penultimate_pixel values to 0 so that the first pixel be compared to rgb(0,0,0)
    penultimate_pixel.r = 0;
    penultimate_pixel.g = 0;
    penultimate_pixel.b = 0;

    PPM_IMG* img = NULL;
    img = ppmOpen("sf2.ppm");
    FILE *fichier = NULL;
	fichier = fopen("blabla", "wb+");
    compressionManager(fichier, img);
    fclose(fichier);
    ppmClose(img);
    rewind(fichier);
    fichier = fopen("blabla", "rb");
    decompressionManager(fichier);
    fclose(fichier);
    ppmSave(img, "/");
    return 0;
}
