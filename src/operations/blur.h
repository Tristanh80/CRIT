#ifndef BLUR_H
#define BLUR_H

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

void blur(SDL_Surface *img, int rate);
void blur_pixels(SDL_Surface *img, int rate, int i, int j);


#endif
