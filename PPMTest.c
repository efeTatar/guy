#include "ppm_lib.c"
#include <time.h>
int main(){
    PPM_IMG* img = NULL;
    int x, y, h= 10, w = 10, r, g, b, chance;
    img = ppmNew(w,h, 255, 3);
    ppmDisplay(img);
    for(y=0;y<h;y++){
        for(x=0;x<w;x++){
            chance = rand()%5;
            if(chance >= 4){
                r = rand()%10;
                g = rand()%10;
                b = rand()%10;
            }
            ppmWrite(img, x, y, pixel(r, g, b));
        }
    }
    ppmDisplay(img);
    ppmSave(img,"testdsogv");
    ppmClose(img);
    return 0;
}
