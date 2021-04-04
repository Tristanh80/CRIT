#include "sym.h"
#include "../import/import.h"

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>

//gcc blur.c border.c filters.c grey.c pixels.c main.c -lSDL -lSDL_image

void symv(SDL_Surface *img)
{
    /* Variables */
    
    int w;
    int h;
    w = img -> w;
    h = img -> h;
    Uint32 pixel_i;
    Uint32 pixel_ni;
    Uint8 r1, r2, g1, g2, b1, b2;

    /* Iterate on each pixels */
    for(int i = 0; i < w/2; i++)
    {
        for(int j = 0; j < h; j++)
        {
            pixel_i = getpixel(img, i, j);
            pixel_ni = getpixel(img, w-i-1, j);
         
            putpixel(img, w-i-1, j, pixel_i);
            putpixel(img, i, j, pixel_ni);
        }
    }
}

void symh(SDL_Surface *img)
{
    /* Variables */
    
    int w;
    int h;
    w = img -> w;
    h = img -> h;
    Uint32 pixel_i;
    Uint32 pixel_ni;
    Uint8 r1, r2, g1, g2, b1, b2;

    /* Iterate on each pixels */
    for(int i = 0; i < h/2; i++)
    {
        for(int j = 0; j < w; j++)
        {
            pixel_i = getpixel(img, j, i);
            pixel_ni = getpixel(img, j, h-i-1);
          
            putpixel(img, j, h-i-1, pixel_i);
            putpixel(img, j, i, pixel_ni);
        }
    }
}



