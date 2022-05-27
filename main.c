#include "ppm_lib.h"

int main(){
    PPM_IMG* img = NULL;
    img = ppmOpen("testdsogv");
    FILE *fichier = NULL;
	fichier = fopen("blabla", "wb+");
    compressionManager(fichier, img);
    fclose(fichier);
    printf("compiled\n");
    ppmClose(img);
    printf("\n");
    fichier = fopen("blabla", "rb");
    rewind(fichier);
    decompressionManager(fichier);
    fclose(fichier);
    ppmSave(img, "fml2");
    printf("SAVED");
    return 0;
}


