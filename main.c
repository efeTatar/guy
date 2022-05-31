#include "ppm_lib.h"

int main(){
    PPM_IMG* img = NULL;
    char nom[1000], autreNom[1000];
    int i, taille, choix;
    
    choix = Menu();
    switch(choix){
        case 1: 
            char *Init = NULL, *cible = NULL;
            FILE *fichier = NULL;
            scanf("%s", nom);
            taille = strlen(nom);
            Init = malloc((taille+9)*sizeof(1));
            Init[0] = 'i';Init[1] = 'm'; Init[2] = 'a'; Init[3] = 'g'; Init[4] = 'e'; Init[5] = 's'; Init[6] = '/';
            for(i=0;i<taille+7;i++){
                Init[i+7] = nom[i];
            }
            img = ppmOpen(Init);
            printf("\nComment voulez vous appeller votre fichier compressé : ");
            scanf("%s",autreNom);
            taille = strlen(autreNom);
            Init = malloc(taille*sizeof(1));
            for(i=0;i<taille;i++){
                cible[i] = autreNom[i];
            }
            fichier = fopen("autreNom", "wb+");
            compressionManager(fichier, img);
            fclose(fichier);
            ppmClose(img);
            printf("\nCOMPILED\n");
    }
    FILE *helo = NULL;

    /*FILE *helo = NULL;
	helo = fopen("blabla", "rb");
    unsigned char b = 0;
    int a;
    for(i=0;i<100;i++){
        fread(&b, sizeof(1), 1, helo);
        printf("\n%u", b);
    }
    fclose(helo);*/
    
    printf("\n");
    fichier = fopen("blabla", "rb");
    rewind(fichier);
    decompressionManager(fichier);
    fclose(fichier);
    ppmSave(img, "fml2");
    printf("SAVED");
    //free(Init);
    return 0;
}





