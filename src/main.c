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





