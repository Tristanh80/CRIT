#ifndef PIXELS_H
#define PIXELS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
SDL_Surface* copy_image(SDL_Surface *img);

#endif
