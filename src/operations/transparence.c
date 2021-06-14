#include "../import/import.h"
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include <stdio.h>

void transparence (SDL_Surface *img, int alpha)
{
  SDL_Surface *ecran = img;
  SDL_Surface *filter = img;

  SDL_Rect position;
  position.x = 0;
  position.y = 0;
  
  SDL_SetColorKey(filter, SDL_SRCCOLORKEY, SDL_MapRGB(filter->format, 0, 0, 0));
  //SDL_SetAlpha(img, SDL_SRCALPHA, 255);
  SDL_SetAlpha(filter, SDL_SRCALPHA, alpha);
  SDL_BlitSurface(filter, NULL, img,  &position);
  
}
