#include "ppm_lib.h"

int main(){
    PPM_IMG* img = NULL;
    img = ppmOpen("testdsogv");
    FILE *fichier = NULL;
	fichier = fopen("blabla", "wb+");
    compressionManager(fichier, img);
    fclose(fichier);
    FILE *helo = NULL;
    ppmClose(img);
    printf("\nCOMPILED\n");

    /*
	helo = fopen("blabla", "rb");
    int i;
    unsigned char b = 0;
    int a;
    for(i=0;i<100;i++){
        fread(&b, sizeof(unsigned char), 1, helo);
        a = (int)b;
        printf("\n%u", a);
    }
    fclose(helo);*/
    
    printf("\n");
    fichier = fopen("blabla", "rb");
    rewind(fichier);
    decompressionManager(fichier);
    fclose(fichier);
    ppmSave(img, "fml2");
    printf("SAVED");
    return 0;
}


