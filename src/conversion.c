#include "ppm_lib.h"

void HexToRGB(char tab[6], pixel_structure *pixel){
	(*pixel).r = 0;
	if(tab[1]>=65){(*pixel).r += tab[1]-55;}
		else{(*pixel).r += tab[1]-48;}
    if(tab[0]>=65){(*pixel).r += (tab[0]-55)*16;}
		else{(*pixel).r += (tab[0]-48)*16;}
    
	(*pixel).g = 0;
    if(tab[3]>=65){(*pixel).g += tab[3]-55;}
		else{(*pixel).g += tab[3]-48;}
    if(tab[2]>=65){(*pixel).g += (tab[2]-55)*16;}
		else{(*pixel).g += (tab[2]-48)*16;}
	
	(*pixel).b = 0;
	if(tab[5]>=65){(*pixel).b += tab[5]-55;}
		else{(*pixel).b += tab[5]-48;}
    if(tab[4]>=65){(*pixel).b += (tab[4]-55)*16;}
		else{(*pixel).b += (tab[4]-48)*16;}
		
}

void DecimalToHex(char tab[6], int dec){
	int Rest = 0, i = 0;
	for(i=0;i<6;i++){
		Rest = dec % 16;
		dec = dec / 16;
		if(Rest<10){tab[5-i]=Rest+48;}
		if(Rest>=10){tab[5-i]=Rest+55;}
	}
}

int ComparePixels(pixel_structure *penultimate_pixel, pixel_structure *ultimate_pixel){
	int same = 1;
	if( (*penultimate_pixel).r != (*ultimate_pixel).r ){same = 0;}
	if( (*penultimate_pixel).g != (*ultimate_pixel).g ){same = 0;}
	if( (*penultimate_pixel).b != (*ultimate_pixel).b ){same = 0;}
	return same;
}

void freadChar(FILE *fichier, unsigned int *value){
	unsigned char read;
	fread(&read, sizeof(unsigned char), 1, fichier);
	*value = (int)read;
}