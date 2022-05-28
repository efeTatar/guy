#include "ppm_lib.h"

int main(){
    PPM_IMG* img = NULL;
    img = ppmOpen("testdsogv");
    FILE *fichier = NULL;
	fichier = fopen("blabla", "wb+");
    compressionManager(fichier, img);
    fclose(fichier);

    unsigned int b = 0;
    FILE *helo = NULL;
	helo = fopen("blabla", "rb");
    int i;
    for(i=0;i<100;i++){
        fread(&b, sizeof(int), 1, helo);
        printf("\n%u", b);
    }
    fclose(helo);

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


