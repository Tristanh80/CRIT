#include "blur.h"
#include "pixels.h"

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>

//gcc blur.c filters.c grey.c pixels.c main.c -lSDL -lSDL_image


void blur(SDL_Surface *img, int rate)
{

    //if rate = 10, then we will "merge" the colors of the 5 previous pixels
    //and 5 following pixels
    rate = rate/2;


    /* Variables */

    int w;
    int h;
    w = img -> w;
    h = img -> h;



    /* Iterate on each pixels */
    for(int i = rate; i < w; i+=rate)
    {
        for(int j = rate; j < h; j+=rate)
        {
            blur_pixels(img, rate, i, j);
        }
    }
}


void blur_pixels(SDL_Surface *img, int rate, int i, int j)
{
    /* Variables  */
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;

    float coef_r = 0;
    float coef_g = 0;
    float coef_b = 0;

    int npixels = rate*rate*4;
    int w;
    int h;
    w = img -> w;
    h = img -> h;

    //the boundaries of the square to blur
    int mini = i-rate;
    int miny = j-rate;
    int maxi = i+rate;
    int maxy = j+rate;


    if(mini < 0)
        mini = 0;

    if(miny < 0)
        miny = 0;

    if(maxi > w)
        maxi = w;

    if(maxy > h)
        maxy = h;


    for(int x = mini; x<maxi; x++)
    {
        for(int y = miny; y<maxy; y++)
        {
            pixel = getpixel(img, x, y);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);

            coef_r += r;
            coef_g += g;
            coef_b += b;
        }
    }

    coef_r /= npixels;
    coef_g /= npixels;
    coef_b /= npixels;


    for(int x = mini; x<maxi; x++)
    {
        for(int y = miny; y<maxy; y++)
        {
            pixel = getpixel(img, x, y);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);

            r = coef_r;
            g = coef_g;
            b = coef_b;

            pixel = SDL_MapRGB(img->format, r, g, b);
            putpixel(img, x, y, pixel);
        }
    }

}
