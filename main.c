#include "ppm_lib.h"

int main(){
    PPM_IMG* img = NULL;
<<<<<<< HEAD
    img = ppmOpen("testdsogv");
=======
    img = ppmOpen("fml");
>>>>>>> 0477c098838ff168436f959bcd07bb28a3ffc49d
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


