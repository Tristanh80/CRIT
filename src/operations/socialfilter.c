#include "../import/import.h"
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include <stdio.h>

void filters(SDL_Surface *img, int choice, int alpha)
{
    SDL_Surface *filter = load_image("filter1.png");

    if (choice == 1)
    {
      filter = load_image("filter1.png");
    }

    if (choice == 2)
    {
      filter = load_image("filter2.png");
    }

    if (choice == 3)
    {
      filter = load_image("filter3.png");
    }
    
    

    SDL_Rect position;
    position.x = 0;
    position.y = 0;

    SDL_SetColorKey(filter, SDL_SRCCOLORKEY, SDL_MapRGB(filter->format, 0, 0, 0));
    SDL_SetAlpha(filter, SDL_SRCALPHA, alpha);
    SDL_BlitSurface(filter, NULL, img,  &position);
  
}
