#include "ppm_lib.c"
#include <time.h>
int main(){
    PPM_IMG* img = NULL;
    int x, y, h= 4, w = 4, r, g, b, chance;
    img = ppmNew(w,h, 255, 3);
    ppmDisplay(img);
    for(y=0;y<h;y++){
        for(x=0;x<w;x++){
            chance = rand()%5;
            if(chance >= 4){
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
    return 0;
}
