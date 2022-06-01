#include "ppm_lib.h"

int main(){
    PPM_IMG* img = NULL;
    FILE *fichier = NULL;
    char nom[1000], autreNom[1000], *Init = NULL, *cible = NULL;;
    int i, taille, choix;
    choix = Menu();
    switch(choix){
        case 1: 
            scanf("%s", nom);
            taille = strlen(nom);
            Init = malloc((taille+8)*sizeof(1));
            Init[0] = 'i'; Init[1] = 'm'; Init[2] = 'a'; Init[3] = 'g'; Init[4] = 'e'; Init[5] = 's'; Init[6] = '/';
            for(i=0;i<taille+7;i++){
                Init[i+7] = nom[i];
                }
            img = ppmOpen(Init);
            printf("\nComment voulez vous appeller votre fichier compressé : ");
            scanf("%s",autreNom);
            taille = strlen(autreNom);
            cible = malloc(taille*sizeof(1));
            for(i=0;i<=taille;i++){
                cible[i] = autreNom[i];
                }
            fichier = fopen(cible, "wb+");
            compressionManager(fichier, img);
            fclose(fichier);
            ppmClose(img);
            printf("\nCOMPILED\n");
            break;
        case 0:
            scanf("%s",autreNom);
            taille = strlen(autreNom);
            cible = malloc((taille+1)*sizeof(char));
            for(i=0;i<taille;i++){
                cible[i] = autreNom[i];
            }
            fichier = fopen(cible, "rb");
            decompressionManager(fichier);
            fclose(fichier);
            printf("SAVED");
            break;
    }
    free(Init);
    free(cible);
    return 0;
}





