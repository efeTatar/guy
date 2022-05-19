#include "ppm_lib.h"

void compressionManager(FILE *fichier, PPM_IMG* img){
    pixel_structure penultimate_pixel, ultimate_pixel
                    ,*penultimate_pixelPointer, *ultimate_pixelPointer;
    penultimate_pixel.r = 0;
    penultimate_pixel.g = 0;
    penultimate_pixel.b = 0;
    penultimate_pixelPointer = &penultimate_pixel;
    ultimate_pixelPointer = &ultimate_pixel;
    int dec;
    char Hex[6] = " ";
    pixel_structure cache[64]; int index;

    int CIP = 0, *CIP_Pointer = NULL;
    CIP_Pointer = &CIP;
    int i, j;
    for(i=1;i<ppmGetHeight(img);i++){
        for(j=1;j<ppmGetWidth(img);j++){
            dec = ppmRead(img, j, i);
            DecimalToHex(Hex, dec);
            HexToRGB(Hex, ultimate_pixelPointer);
            write_EVA_BLK_SAME(fichier, penultimate_pixelPointer,ultimate_pixelPointer, CIP_Pointer, cache);
            penultimate_pixel = ultimate_pixel;
        } 
    }
}

void write_EVA_BLK_SAME(FILE *fichier, pixel_structure *penultimate_pixelPointer, 
                        pixel_structure *ultimate_pixelPointer, int *CIP_Pointer, pixel_structure cache[64]){
    int same;
    printf("same");
    same = ComparePixels(penultimate_pixelPointer, ultimate_pixelPointer);
            if(same == 1){
                *CIP_Pointer++;
                if(*CIP_Pointer==62){*CIP_Pointer +=191; fwrite(CIP_Pointer, sizeof(int), 1, fichier); *CIP_Pointer = 0;}
            }
            else
            {
                if(*CIP_Pointer>0){*CIP_Pointer +=191; fwrite(CIP_Pointer, sizeof(int), 1, fichier);}
                write_EVA_BLK_INDEX(fichier, penultimate_pixelPointer,ultimate_pixelPointer, CIP_Pointer, cache);
            }
}

void write_EVA_BLK_INDEX(FILE *fichier, pixel_structure *penultimate_pixelPointer, 
                        pixel_structure *ultimate_pixelPointer, int *CIP_Pointer, pixel_structure cache[64]){
    int index;
    index = (3*(*ultimate_pixelPointer).r + 5*(*ultimate_pixelPointer).g + 7*(*ultimate_pixelPointer).b)%64;
    if(ComparePixels((cache+index), ultimate_pixelPointer)==1){
        fwrite(&index, sizeof(int), 1, fichier);    
    }
    else{
        write_EVA_BLK_DIFF(fichier, penultimate_pixelPointer,ultimate_pixelPointer, CIP_Pointer, cache);
    }
}

void write_EVA_BLK_DIFF(FILE *fichier, pixel_structure *penultimate_pixelPointer, 
                        pixel_structure *ultimate_pixelPointer, int *CIP_Pointer, pixel_structure cache[64]){
    int r_diff, g_diff, b_diff;
    int intervalCheck = 1;
    r_diff = (*penultimate_pixelPointer).r - (*ultimate_pixelPointer).r;
    g_diff = (*penultimate_pixelPointer).g - (*ultimate_pixelPointer).g;
    b_diff = (*penultimate_pixelPointer).b - (*ultimate_pixelPointer).b;
    if(r_diff > 2 || r_diff < -1){intervalCheck = 0;}
    if(g_diff > 2 || g_diff < -1){intervalCheck = 0;}
    if(b_diff > 2 || b_diff < -1){intervalCheck = 0;}
    if(intervalCheck==1){
        r_diff += 2; g_diff += 2; b_diff += 2;
        unsigned int value = 0;
        (value & 0x03) == 0x01;
        value = value << 2;
        (value & 0x03) == r_diff;
        value = value << 2;
        (value & 0x03) == g_diff;
        value = value << 2;
        (value & 0x03) == b_diff;
        fwrite(&value, sizeof(unsigned int), 1, fichier);
    }
    else{
        write_EVA_BLK_LUMA(fichier, penultimate_pixelPointer,ultimate_pixelPointer, CIP_Pointer, cache);
    }
}

void write_EVA_BLK_LUMA(FILE *fichier, pixel_structure *penultimate_pixelPointer, 
                        pixel_structure *ultimate_pixelPointer, int *CIP_Pointer, pixel_structure cache[64]){
    int r_diff, g_diff, b_diff;
    int intervalCheck = 1;
    unsigned int value = 0;
    r_diff = (*penultimate_pixelPointer).r - (*ultimate_pixelPointer).r;
    g_diff = (*penultimate_pixelPointer).g - (*ultimate_pixelPointer).g;
    b_diff = (*penultimate_pixelPointer).b - (*ultimate_pixelPointer).b;
    if(g_diff > 31 || g_diff < -32){intervalCheck = 0;}
    if((r_diff-g_diff) > 7 || (r_diff-g_diff) < -8){intervalCheck = 0;}
    if((b_diff-g_diff) > 7 || (b_diff-g_diff) < -8){intervalCheck = 0;}
    if(intervalCheck==1){
        (value & 0x03) == 0x03;
        value = value << 6;
        (value & 0x3F) == g_diff + 32;
        fwrite(&value, sizeof(unsigned int), 1, fichier);
        value = 0;
        (value & 0xF) == r_diff-g_diff + 8;
        value = value << 4;
        (value & 0xF) == b_diff-g_diff + 8;
    }
    else{
        write_EVA_BLK_RGB(fichier, penultimate_pixelPointer,ultimate_pixelPointer, CIP_Pointer, cache);
    }
   
}

void write_EVA_BLK_RGB(FILE *fichier, pixel_structure *penultimate_pixelPointer, 
                        pixel_structure *ultimate_pixelPointer, int *CIP_Pointer, pixel_structure cache[64]){
    fwrite("0xFE", sizeof(int), 1, fichier);
    fwrite(&ultimate_pixelPointer->r, sizeof(int), 1, fichier);
    fwrite(&ultimate_pixelPointer->g, sizeof(int), 1, fichier);
    fwrite(&ultimate_pixelPointer->b, sizeof(int), 1, fichier);
}

void write_EVA_BLK_DEBUG(FILE *fichier, pixel_structure *penultimate_pixelPointer, 
                        pixel_structure *ultimate_pixelPointer, int *CIP_Pointer, pixel_structure cache[64]){
    fwrite("0xFF", sizeof(int), 1, fichier);
}

void writeHeader(FILE *fichier, PPM_IMG *img){
    int w = ppmGetWidth (img),
        h = ppmGetHeight(img),
        rng = ppmGetColors(img),
        nbColors = ppmGetRange (img);

    fwrite(&w, sizeof(int), 1, fichier);
    fwrite(&h, sizeof(int), 1, fichier);
    fwrite(&rng, sizeof(int), 1, fichier);
    fwrite(&nbColors, sizeof(int), 1, fichier);
}

