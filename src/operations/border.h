#ifndef BORDER_H
#define BORDER_H

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include "../import/import.h"

void border(SDL_Surface *img, int border_width);
void dashborder(SDL_Surface *img, int border_width, int space);


#endif
