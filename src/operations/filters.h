#ifndef FILTER_H
#define FILTER_H

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

void filter(SDL_Surface *img, char color);
void red(SDL_Surface *img);
void green(SDL_Surface *img);
void blue(SDL_Surface *img);

#endif
