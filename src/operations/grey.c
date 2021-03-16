#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>


void greyscale(SDL_Surface *img)
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
            coef_r = r * 0.3;
            coef_g = g * 0.59;
            coef_b = b * 0.11;
            r = coef_r + coef_g + coef_b;
            g = coef_r + coef_g + coef_b;
            b = coef_r + coef_g + coef_b;
            pixel = SDL_MapRGB(img->format, r, g, b);
            putpixel(img,i,j,pixel);
        }
    }
}


void monochromatic(SDL_Surface *img)
{
}


