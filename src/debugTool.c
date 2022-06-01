#include "ppm_lib.h"

<<<<<<< HEAD
void debugtool(){
=======
int main(){
>>>>>>> main
    PPM_IMG* img = NULL;
    int x, y, h= 50, w = 50, r, g, b, chance;
    img = ppmNew(w,h, 255, 3);
    ppmDisplay(img);
    for(y=0;y<h;y++){
        for(x=0;x<w;x++){
            chance = rand()%5;
            if(chance >= 80){
                r = (rand()%256);
                g = (rand()%256);
                b = (rand()%256);
            }
            ppmWrite(img, x, y, pixel(r, g, b));
        }
    }
    ppmDisplay(img);
    ppmSave(img,"testdsogv");
    ppmClose(img);
}

