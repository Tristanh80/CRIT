#include "rotate.h"
#include "../import/import.h"

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>



void rotate(SDL_Surface *img, char angle)
{
    if(angle != 'r' && angle != 'l')
        errx(EXIT_FAILURE, "Wrong rotate angle value");



    /* Variables */
    Uint32 pixel;
    Uint32 pixel_ni;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int w;
    int h;
    int nw;
    int nh;
    w = img -> w;
    h = img -> h;
    nw = h;
    nh = w;

    img->h = nh;
    img->w = nw;

    SDL_Surface *nimg = malloc(sizeof(SDL_Surface));
    nimg->format = img->format;
    nimg->w = nw;
    nimg->h = nh;

    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
           
            pixel_ni = getpixel(nimg, j ,i);
            pixel_ni = SDL_MapRGB(nimg->format, r, g, b);
        }
    }


    //rotate 90 degrees right
    if(angle == 'z')
    {
        for(int i = 0; i < nw; i++)
        {
            for(int j = 0; j < nh; j++)
            {
                //pixel = Mat[i*w+j];
                putpixel(nimg, i, j, pixel);
            }
        }
    }

/*
    //rotate 90 degrees left
    else
    {
        for(int i = 0; i < w; i++)
        {
            for(int j = 0; j < h; j++)
            {
                pixel = Mat[];
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                pixel = SDL_MapRGB(img->format, r, g, b);
                Mat[i*w+j] = pixel;
            }
        }

    }
*/
    img = nimg;
    free(nimg);
}


