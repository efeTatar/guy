#include "ppm_lib.h"

int Menu(){
    int choix;
    printf("        || DE(COM)PRESSION ||\nQue voulez vous faire :\n   -COMPRESSION (tapez 1).\n   -DECOMPRESSION (tapez 2);");
    scanf("%d",&choix);
    while(choix != 1 && choix != 0){
        printf("Reeur veuillez choisir un nombre entre 0 et 1");
        scanf("%d",&choix);
    }
    switch(choix){
        case 1:
            printf("\nncompression\nQuelle image voulez vous compresser (veuillez a bien deposer une image au format PPM.\n");
            return 1;
        case 0:
            printf("\nDecompression\nQuel fichier voulez-vous decompresser : ");
            return 0;
        default: 
            printf("ERROR");
            break;
    }
    return -1;
}
