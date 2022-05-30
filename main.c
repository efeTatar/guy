#include "ppm_lib.h"

int main(){
    PPM_IMG* img = NULL;
    char nom[100], *Init = NULL;
    int i, taille;
    scanf("%s", nom);
    taille = strlen(nom);
    Init = malloc((taille+9)*sizeof(1));
    Init[0] = 'i';Init[1] = 'm'; Init[2] = 'a'; Init[3] = 'g'; Init[4] = 'e'; Init[5] = 's'; Init[6] = '/';
    for(i=0;i<taille+7;i++){
        Init[i+7] = nom[i];
    }
    printf("%s", Init);
    printf("\n");
    img = ppmOpen(Init);
    FILE *fichier = NULL;
	fichier = fopen("blabla", "wb+");
    //compressionManager(fichier, img);
    fclose(fichier);
    FILE *helo = NULL;
    ppmClose(img);
    printf("\nCOMPILED\n");

    
	helo = fopen("blabla", "rb");
    unsigned char b = 0;
    int a;
    for(i=0;i<100;i++){
        fread(&b, sizeof(1), 1, helo);
        printf("\n%u", b);
    }
    fclose(helo);
    
    printf("\n");
    fichier = fopen("blabla", "rb");
    rewind(fichier);
    //decompressionManager(fichier);
    fclose(fichier);
    ppmSave(img, "fml2");
    printf("SAVED");
    free(Init);
    return 0;
}





