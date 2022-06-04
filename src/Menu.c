#include "ppm_lib.h"
#include <unistd.h>

int Menu(){
    char choix;
    printf("\n                                                Welcome into\n                                            || DE(COM)PRESSION ||\nIn this program, you will have the possibility either zip a picture or unzip a compressed file.\n                                            What do you want to do ? :\n          -COMPRESSION (type 1).                                     -DECOMPRESSION (type 2).\n");
    scanf("%c",&choix);
    while(choix!='1' && choix!='2'){
        usleep(10); 
        printf("\nError, please choose a number beetwen 1 and 2.");
        scanf("%c", &choix);
    }
    switch(choix){
        case '1':
            printf("\n| COMPRESSION |\nWich picture would you want to use (please be careful, only upload PPM).\n");
            return 1;
        case '2':
            printf("\n| DECOMPRESSION |\nWich file would you want to unzip : ");
            return 0;
        default: 
            printf("ERROR");
            break;
    }
    return -1;
}
