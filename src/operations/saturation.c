#include "saturation.h"
#include "../import/import.h"

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include <stdio.h>
#include <math.h>

void saturation_level(SDL_Surface *img, char level)
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 coef_r;
    Uint8 coef_g;
    Uint8 coef_b;
    int w, h;
    w = img -> w; 
    h = img -> h;


    if (level == '0')//negative saturation
    {
        for(int i = 0; i < w; i++)
        {
            for(int j = 0; j < h; j++)
            {
                pixel = getpixel(img, i, j);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                coef_r = r*0.3 + g*0.59 + b*0.11;
                coef_g = r*0.3 + g*0.59 + b*0.11;
                coef_b = r*0.3 + g*0.59 + b*0.11;

                pixel = SDL_MapRGB(img->format, coef_r, coef_g, coef_b);
                putpixel(img, i, j, pixel);
            }
        }
    }

    if (level == '1')//medium saturation
    {
        for(int i = 0; i < w; i++)
        {
            for(int j = 0; j < h; j++)
            {
                pixel = getpixel(img, i, j);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                if (r > b && r > g)
                    r += (255 - r)*0.11;
                else if (b > r && b > g)
                    b += (255 - b)*0.11;
                else if (g > r && g > b)
                    g += (255 - g)*0.11;

                pixel = SDL_MapRGB(img->format, r, g, b);
                putpixel(img, i, j, pixel);
            }
        }
    }


    if (level == '2')//high saturation
    {
        for(int i = 0; i < w; i++)
        {
            for(int j = 0; j < h; j++)
            {
                pixel = getpixel(img, i, j);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                if (r > b && r > g)
                    r += (255 - r)*0.2;
                else if (b > r && b > g)
                    b += (255 - b)*0.2;
                else if (g > r && g > b)
                    g += (255 - g)*0.2;

                pixel = SDL_MapRGB(img->format, r, g, b);
                putpixel(img, i, j, pixel);
            }
        }
    }

}
