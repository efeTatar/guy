#include <stdio.h>

int main(){
    int choix; char a;
    FILE* fichier;
    fichier = fopen("titre.txt","r");
    if(fichier == NULL){
        printf("ERROR");
        exit(1);
    }
    do{
        a = fgetc(fichier);
        printf("%c",a);
    }while(a != EOF);
    printf("        || DE(COM)PRESSION ||\nQue voulez vous faire :\n-Compression (tapez 1):\n-DECOMPRESSION (tapez 2):\n");
    scanf("%d",&choix);
    switch(choix){
        case 1:
            printf("\ncompression\n");
            break;
        case 0:
            printf("\nDecompression\n");
            break;
        default : 
            printf("\nERROR\n");
    }
    fclose(fichier);
    return 0;
}

