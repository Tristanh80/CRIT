#include "border.h"
#include "../import/import.h"

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>

//gcc grey.c pixels.c main.c -lSDL -lSDL_image

void border(SDL_Surface *img)
{
    /* Variables */
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;

    int w;
    int h;
    w = img -> w;
    h = img -> h;

    int border_width = 15;
    /* Iterate over each pixels concerned by the border */
    for(int i = 0; i < border_width; i++)
    {
        for(int j = 0; j < h; j++)
        {
            pixel = getpixel(img, i, j);
            r = 0;
            g = 0;
            b = 0;
            pixel = SDL_MapRGB(img->format, r, g, b);
            putpixel(img, i, j, pixel);
        }
    }

    for(int i = border_width; i < w - border_width; i++)
    {
        for(int j = 0; j < border_width; j++)
        {
            pixel = getpixel(img, i, j);
            r = 0;
            g = 0;
            b = 0;
            pixel = SDL_MapRGB(img->format, r, g, b);
            putpixel(img, i, j, pixel);
        }
    }

    for(int i = w - border_width; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            pixel = getpixel(img, i, j);
            r = 0;
            g = 0;
            b = 0;
            pixel = SDL_MapRGB(img->format, r, g, b);
            putpixel(img, i, j, pixel);
        }
    }

    for(int i = border_width; i < w - border_width; i++)
    {
        for(int j = h - border_width; j < h; j++)
        {
            pixel = getpixel(img, i, j);
            r = 0;
            g = 0;
            b = 0;
            pixel = SDL_MapRGB(img->format, r, g, b);
            putpixel(img, i, j, pixel);
        }
    }
}







