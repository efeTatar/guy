#include "ppm_lib.h"

int main(){
    PPM_IMG* img = NULL;
    img = ppmOpen("fml");
    FILE *fichier = NULL;
	fichier = fopen("blabla", "wb+");
    compressionManager(fichier, img);
    fclose(fichier);
    printf("compiled");
    ppmClose(img);
    
    fichier = fopen("blabla", "rb");
    rewind(fichier);
    decompressionManager(fichier);
    fclose(fichier);
    ppmSave(img, "fml2");
    printf("SAVED");
    return 0;
}


