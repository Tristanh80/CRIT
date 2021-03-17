#include "filters.h"
#include "pixels.h"

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>

//gcc filters.c grey.c pixels.c main.c -lSDL -lSDL_image


void filter(SDL_Surface *img, char color)
{
    if(color == 'r')
        red(img);

    else if(color == 'g')
        green(img);

    else if(color == 'b')
        blue(img);

    else
        errx(EXIT_FAILURE, "Wrong color");
}


void red(SDL_Surface *img)
{

    /* Variables */
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    float coef_r;
    float coef_g;
    float coef_b;
    float mean;
    int w;
    int h;
    w = img -> w;
    h = img -> h;

    /* Iterate on each pixels */
    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            if(r < b*1.4 || r < g*1.4)
            {
                coef_r = r*0.3;
                coef_g = g*0.59;
                coef_b = b*0.11;
                mean = coef_r + coef_g + coef_b;
                r = mean;
                g = mean;
                b = mean;
            }

            /*
               else
               {
            //g *= 0.5;
            //b *= 0.5;
            }
             */

            pixel = SDL_MapRGB(img->format, r, g, b);
            putpixel(img, i, j, pixel);
        }
    }
}


void green(SDL_Surface *img)
{

    /* Variables */
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    float coef_r;
    float coef_g;
    float coef_b;
    float mean;
    int w;
    int h;
    w = img -> w;
    h = img -> h;

    /* Iterate on each pixels */
    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            if(g < b || g < r)
            {
                coef_r = r*0.3;
                coef_g = g*0.59;
                coef_b = b*0.11;
                mean = coef_r + coef_g + coef_b;
                r = mean;
                g = mean;
                b = mean;
            }

            /*
               else
               {
            //r *= 0.5;
            //b *= 0.5;
            }
             */

            pixel = SDL_MapRGB(img->format, r, g, b);
            putpixel(img, i, j, pixel);
        }
    }
}

void blue(SDL_Surface *img)
{

    /* Variables */
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    float coef_r;
    float coef_g;
    float coef_b;
    float mean;
    int w;
    int h;
    w = img -> w;
    h = img -> h;

    /* Iterate on each pixels */
    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            if(b < r*0.9 || b < g*0.9)
            {
                coef_r = r*0.3;
                coef_g = g*0.59;
                coef_b = b*0.11;
                mean = coef_r + coef_g + coef_b;
                r = mean;
                g = mean;
                b = mean;
            }

            /*
               else
               {
            //g *= 0.5;
            //r *= 0.5;
            }
             */

            pixel = SDL_MapRGB(img->format, r, g, b);
            putpixel(img, i, j, pixel);
        }
    }


}





