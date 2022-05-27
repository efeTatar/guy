#include "ppm_lib.h"

int main(){
    PPM_IMG* img = NULL;
<<<<<<< HEAD
    img = ppmOpen("calvinhobbes.ppm");
=======
    img = ppmOpen("nintendo.ppm");
>>>>>>> main
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
    ppmSave(img, "fml");
    printf("SAVED");
    return 0;
}


