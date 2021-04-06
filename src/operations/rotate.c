#include "rotate.h"
#include "../import/import.h"

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>



SDL_Surface *rotate(SDL_Surface *img, char angle)
{
    if(angle != 'r' && angle != 'l')
        errx(EXIT_FAILURE, "Wrong rotate angle value");



    /* Variables */
    Uint32 pixel;
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

    SDL_Surface *nimg = SDL_CreateRGBSurface(SDL_HWSURFACE,
            nw,
            nh,
            img -> format -> BitsPerPixel,0,0,0,0);

    //rotate 90 degrees right
    if(angle == 'r')
    {
        for(int i = 0; i < w; i++)
        {
            for(int j = 0; j < h; j++)
            {
                pixel = getpixel(img, i, j);
                SDL_GetRGB(pixel, img -> format, &r, &g, &b);
                pixel = SDL_MapRGB(img -> format, r, g, b);
                putpixel(nimg, nw-1-j, i, pixel);
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

    SDL_FreeSurface(img);
    return nimg;
}


