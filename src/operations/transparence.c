#include "saturation.h"
#include "../import/import.h"

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include <stdio.h>

void transparence (SDL_Surface *img, int level)
{
    SDL_SetColorKey(img, SDL_SRCCOLORKEY, SDL_MapRGB(img->format, 0, 0, 255));
    SDL_SetAlpha(img, SDL_SRCALPHA, level);
}
