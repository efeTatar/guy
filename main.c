#include "ppm_lib.h"

int main(){

    pixel_structure penultimate_pixel, ultimate_pixel, 
        *penultimate_pixelPointer, *ultimate_pixelPointer;  

    //sets the initial penultimate_pixel values to 0 so that the first pixel be compared to rgb(0,0,0)
    penultimate_pixel.r = 0;
    penultimate_pixel.g = 0;
    penultimate_pixel.b = 0;

    PPM_IMG* img = NULL;
    img = ppmOpen("calvinhobbes.ppm");
    //FILE *fichier = NULL;
    int x = 1, y = 1;
	int total = 0;
	int dec;
    printf("%d\n", ppmRead(img, x, y));
    dec = ppmRead(img, x, y);
    char Hex[6] = " ";
    DecimalToHex(Hex, dec);
    
    penultimate_pixelPointer = &penultimate_pixel;
    HexToRGB(Hex, penultimate_pixelPointer);
    printf("RGB(%d, %d, %d)\n", penultimate_pixel.r, penultimate_pixel.g, penultimate_pixel.b);
    printf("Hello Efe\n");

    int nbrIdenticalConsecutivePixels, *nbrIdenticalConsecutivePixels;;

    //FILE *fichier = NULL;
	//fichier = fopen("blabla", "wb+");
    //fclose(fichier);

    ppmClose(img);
    //fclose(fichier);
    return 0;
}
