#include <stdio.h>

int main(){
    int choix;
    printf("        || DE(COM)PRESSION ||\nQue voulez vous faire :\n-Compression (tapez 1).\n-DECOMPRESSION (tapez 2);");
    scanf("%d",&choix);
    switch(choix){
        case 1:
            printf("\ncompression\n");
            break;
        case 0:
            printf("\nDecompression\n");
            break;
    }
    return 0;
}
