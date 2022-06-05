#include "ppm_lib.h"

// Manages the program
int main(){
    PPM_IMG* img = NULL;
    FILE *fichier = NULL;
    char name[1000], *path = NULL;
    int i, taille, choix;
    // Asks user if they want to compress or decompress
    choix = Menu();
    switch(choix){
<<<<<<< HEAD
        case 1:
            scanf("%s", name);
            path = malloc((strlen(name)+9)*sizeof(char));
            path = nameToPath(name,0);
            img = ppmOpen(path);
            free(path);
            printf("\nHow do you want to name your zipped file : ");
            scanf("%s",name);
            path = malloc((strlen(name)+9)*sizeof(char));
            path = nameToPath(name, 1);
            fichier = fopen(path, "wb+");
=======
        // Compression and naming process
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
>>>>>>> main
            compressionManager(fichier, img);
            fclose(fichier);
            ppmClose(img);
            printf("\nCOMPRESSED FILE COMPILED\n");
            break;
        // Decompression and naming process
        case 0:
            scanf("%s",name);
            path = malloc((strlen(name)+9)*sizeof(char));
            path = nameToPath(name, 1);
            fichier = fopen(path, "rb");
            decompressionManager(fichier);
            fclose(fichier);
            printf("\nIMAGE COMPILED\n");
            break;
    }
    free(path);
    return 0;
}





