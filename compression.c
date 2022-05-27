#include "ppm_lib.h"

void compressionManager(FILE *fichier, PPM_IMG* img){
    pixel_structure penultimate, ultimate;
    penultimate.r = 0;
    penultimate.g = 0;
    penultimate.b = 0;
    pixel_structure *cache; int index;
    cache = malloc(64 * sizeof(pixel_structure));
    char Hex[6] = " ";
    int CIP = 0;
    int x, y;
    writeHeader(fichier, img);
    for(y=0;y<ppmGetHeight(img);y++){
        for(x=0;x<ppmGetWidth(img);x++){
            DecimalToHex(Hex, ppmRead(img, x, y));
            HexToRGB(Hex, &ultimate);
            printf("(%d, %d, %d)", ultimate.r, ultimate.g, ultimate.b);
            write_EVA_BLK_SAME(fichier, &penultimate, &ultimate, &CIP, cache);
            penultimate = ultimate;
            index = (3*ultimate.r + 5*ultimate.g + 7*ultimate.b)%64;
            cache[index] = ultimate;
            //printf("(%d %d) ", x, y);
            if(CIP==62){
                CIP+=191;
                fwrite(&CIP, sizeof(int), 1, fichier);
                CIP = 0;
            }
        }
    }

}

void write_EVA_BLK_SAME(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    if(ComparePixels(penultimatePointer, ultimatePointer)==1){
        printf("same ");
        *CIP_Pointer++;
        return;
    }
    else{
        if(*CIP_Pointer>0){
            *CIP_Pointer += 191;
            fwrite(CIP_Pointer, sizeof(int), 1, fichier);
            *CIP_Pointer = 0;
        }
        write_EVA_BLK_INDEX(fichier, penultimatePointer,ultimatePointer, CIP_Pointer, cache);
    }
}

void write_EVA_BLK_INDEX(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    int index;
    index = (3*(*ultimatePointer).r + 5*(*ultimatePointer).g + 7*(*ultimatePointer).b)%64;
    if(ComparePixels((cache+index), ultimatePointer)==1){
        printf("index ");
        fwrite(&index, sizeof(int), 1, fichier);  
        //printf("%u ", index);
        return;
    }
    else{
        write_EVA_BLK_DIFF(fichier, penultimatePointer,ultimatePointer, CIP_Pointer, cache);
    }
}

void write_EVA_BLK_DIFF(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    int check = 1;
    int rdiff = (*ultimatePointer).r-(*penultimatePointer).r, 
        gdiff = (*ultimatePointer).g-(*penultimatePointer).g,
        bdiff = (*ultimatePointer).b-(*penultimatePointer).b;
    if(rdiff>1 || rdiff<-2){check=0;}
    if(gdiff>1 || gdiff<-2){check=0;}
    if(bdiff>1 || bdiff<-2){check=0;}
    if(check==1){
        printf("diff ");
        rdiff += 2;
        gdiff += 2;
        bdiff += 2;
        unsigned int byte = 0;
        byte = 1; byte = byte << 2;
        byte = byte | rdiff;
        byte = byte << 2;
        byte = byte | gdiff;
        byte = byte << 2;
        byte = byte | bdiff;
        //printf("%u ", byte);
        fwrite(&byte, sizeof(int), 1, fichier); 
        return;
    }
    write_EVA_BLK_LUMA(fichier, penultimatePointer,ultimatePointer, CIP_Pointer, cache);
}

void write_EVA_BLK_LUMA(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    int rdiff = (*ultimatePointer).r-(*penultimatePointer).r, 
        gdiff = (*ultimatePointer).g-(*penultimatePointer).g,
        bdiff = (*ultimatePointer).b-(*penultimatePointer).b;
    int check = 1;
    if(gdiff>31 || gdiff<-32){check=0;}
    int rgdiff = rdiff - gdiff, bgdiff = bdiff - gdiff;
    if(rgdiff>7 || rgdiff<-8){check=0;}
    if(bgdiff>7 || bgdiff<-8){check=0;}
    if(check==1){
        printf("luma ");
        unsigned int byte;
        byte = 2;
        byte = byte << 6;
        gdiff += 32;
        byte = byte | gdiff;
        //printf("%u ", byte);
        fwrite(&byte, sizeof(int), 1, fichier);
        byte = 0;
        rgdiff += 8;
        bgdiff += 8;
        byte = byte | rgdiff;
        byte = byte << 4;
        byte = byte | bgdiff;
        //printf("%u ", byte);
        fwrite(&byte, sizeof(int), 1, fichier);
        return;
    }
    write_EVA_BLK_RGB(fichier, penultimatePointer,ultimatePointer, CIP_Pointer, cache);
}

void write_EVA_BLK_RGB(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    printf("rgb ");
    fwrite("0xFE", sizeof(int), 1, fichier);
    fwrite(&ultimatePointer->r, sizeof(int), 1, fichier);
    fwrite(&ultimatePointer->g, sizeof(int), 1, fichier);
    fwrite(&ultimatePointer->b, sizeof(int), 1, fichier);
}

void write_EVA_BLK_DEBUG(FILE *fichier, pixel_structure *penultimatePointer, 
                        pixel_structure *ultimatePointer, int *CIP_Pointer, pixel_structure cache[64]){
    fwrite("0xFF", sizeof(int), 1, fichier);
}

void writeHeader(FILE *fichier, PPM_IMG *img){
    int w = ppmGetWidth (img),
        h = ppmGetHeight(img),
        rng = ppmGetRange (img),
        nbColors = ppmGetColors(img);
    fwrite(&w, sizeof(int), 1, fichier);
    fwrite(&h, sizeof(int), 1, fichier);
    fwrite(&rng, sizeof(int), 1, fichier);
    fwrite(&nbColors, sizeof(int), 1, fichier);
}

