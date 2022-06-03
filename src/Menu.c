#include "ppm_lib.h"
#include <unistd.h>

int Menu(){
    char choix;
    printf("\n                                            || DE(COM)PRESSION ||\nDans ce programme, vous aurez la possibilité de compresser une image puis ensuite de pouvoir la decompresser.\n                                            Que voulez vous faire :\n          -COMPRESSION (tapez 1).                                     -DECOMPRESSION (tapez 2);\n");
    scanf("%c",&choix);
    while(choix!='1' && choix!='2'){
        usleep(10); 
        printf("\nErreur, veuillez choisir un nombre entre 1 et 2.");
        scanf("%c", &choix);
    }
    switch(choix){
        case '1':
            printf("\n| COMPRESSION |\nQuelle image voulez vous compresser (veuillez a bien deposer une image au format PPM).\n");
            return 1;
        case '2':
            printf("\n| DECOMPRESSION |\nQuel fichier voulez-vous decompresser : ");
            return 0;
        default: 
            printf("ERROR");
            break;
    }
    return -1;
}
