#ifndef IMPORT_H
#define IMPORT_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void wait_for_keypressed();
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
SDL_Surface* copy_image(SDL_Surface *img);

#endif
