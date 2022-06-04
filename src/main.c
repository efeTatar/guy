#include "ppm_lib.h"

int main(){
    PPM_IMG* img = NULL;
    FILE *fichier = NULL;
    char name[1000], *path = NULL;
    int i, taille, choix;
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
            printf("\nCOMPILED\n");
            break;
        case 0:
            scanf("%s",name);
            path = malloc((strlen(name)+9)*sizeof(char));
            path = nameToPath(name, 1);
            fichier = fopen(path, "rb");
            decompressionManager(fichier);
            fclose(fichier);
            printf("SAVED");
            break;
    }
    free(path);
    return 0;
}





