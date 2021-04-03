#include "../import/import.h"
#include "grey.h"
#include "filters.h"
#include "blur.h"
#include "border.h"
#include "rotate.h"
#include "sym.h"

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include <string.h>

/*
   SDL_Surface* load_image(char *path)
   {
   SDL_Surface *img;

   img = IMG_Load(path);
   if (!img)
   errx(3, "can't load %s: %s", path, IMG_GetError());

   return img;
   }


   SDL_Surface* display_image(SDL_Surface *img)
   {
   SDL_Surface *screen;

// Set the window to the same size as the image
screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
if (screen == NULL)
{
// error management
errx(1, "Couldn't set %dx%d video mode: %s\n",
img->w, img->h, SDL_GetError());
}

// Blit onto the screen surface
if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
warnx("BlitSurface error: %s\n", SDL_GetError());

// Update the screen
SDL_UpdateRect(screen, 0, 0, img->w, img->h);

// return the screen for further uses
return screen;
}

void wait_for_keypressed()
{
SDL_Event event;

// Wait for a key to be down.
do
{
SDL_PollEvent(&event);
} while(event.type != SDL_KEYDOWN);

// Wait for a key to be up.
do
{
SDL_PollEvent(&event);
} while(event.type != SDL_KEYUP);
}


 */





int main(int argc, char* argv[])
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    void init_sdl();

    image_surface = load_image("my_image.jpg");
    screen_surface = display_image(image_surface);

    if(argc == 1)
    {

        wait_for_keypressed();

        rotate(image_surface, 'r');
        screen_surface = display_image(image_surface);

        wait_for_keypressed();

        monochromatic(image_surface);
        screen_surface = display_image(image_surface);

        wait_for_keypressed();

        wait_for_keypressed();

        border(image_surface);
        screen_surface = display_image(image_surface);

        wait_for_keypressed();
        //SDL_SaveBMP(screen_surface, "savebmp.bmp");
    }



    else if(argc == 3 && strcmp(argv[1], "filter") == 0)
    {
        wait_for_keypressed();

        char color = *argv[2];
        filter(image_surface, color);
        screen_surface = display_image(image_surface);

        wait_for_keypressed();


    }

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

    return 0;

}


