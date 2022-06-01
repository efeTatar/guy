#include "ppm_lib.h"
#include <unistd.h>

void debugtool(){
    PPM_IMG* img = NULL;
    int x, y, h= 1000, w = 1000, r, g, b, chance;
    img = ppmNew(w,h, 255, 3);
    ppmDisplay(img);
    int a = 0;
    for(y=0;y<h;y++){
        for(x=0;x<w;x++){
            /*chance = rand()%100;
            if(chance >= 80){
                r = (rand()%256);
                g = (rand()%256);
                b = (rand()%256);
            }
            ppmWrite(img, x, y, pixel(r, g, b));*/
            if(a==0){
                r = (rand()%256);
                usleep(10); 
                g = (rand()%256);
                usleep(10); 
                b = (rand()%256);
                a=100;
            }
            ppmWrite(img, x, y, pixel(r, g, b));
            a--;
        }
    }
    ppmDisplay(img);
    ppmSave(img,"testimage");
    ppmClose(img);
}

