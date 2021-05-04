#include "sepia.h"
#include "../import/import.h"

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>


int limit(int rgb)
{
    rgb = rgb>255 ? 255 : rgb;
    return rgb;
}



void sepia(SDL_Surface *img)
{
    /* Variables */
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    float coef_r;
    float coef_g;
    float coef_b;
    int w;
    int h;
    w = img -> w;
    h = img -> h;

    /* Iterate on each pixels and greyscale */
    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            /* Apply luminance on r g b */
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            coef_r = limit(0.393*r+0.769*g+0.189*b);
            coef_g = limit(0.349*r+0.686*g+0.168*b);
            coef_b = limit(0.272*r+0.534*g+0.131*b);
            pixel = SDL_MapRGB(img->format, coef_r,coef_g, coef_b);
            putpixel(img, i, j, pixel);
        }
    }
}
