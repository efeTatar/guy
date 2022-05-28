#include <stdio.h>

int main(){
    unsigned int byte = 254;
    switch(byte & 0xC0){
       case 0xC0:
            if(byte == 0xFE){
                printf("0xFE - RGB \n");
                break;
            }                          
            if(byte  == 0xFF ){
                printf("OxFF - debug \n");
                break;
            }
            else{
                printf("SAME - 0xC0\n");
                break;
            }
            
        case 0x00:
            printf("index - 0x00\n");
            break;
        case 0x40:
            printf("DIFF - 0x40\n");
            break;
        case 0x80:
            printf("LUMA - 0x80");
            break;
    }
    return 0;
}