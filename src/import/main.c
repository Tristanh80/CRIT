#include "import.h"


#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>

int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    void init_sdl();

    image_surface = load_image("my_image.jpg");
    SDL_SaveBMP(image_surface,"Example.bmp");
    screen_surface = display_image(image_surface);

    wait_for_keypressed();

    greyscale(image_surface);
    //screen_surface = display_image(image_surface);

    //wait_for_keypressed();

    SDL_Surface *img2 = copy_image(image_surface);

    screen_surface = display_image(img2);

    wait_for_keypressed();

    SDL_SaveBMP(screen_surface, "savebmp.bmp");

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

    return 0;

}


