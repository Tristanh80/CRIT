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
    screen_surface = display_image(image_surface);

    wait_for_keypressed();

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

    SDL_Surface *img2 = copy_image(image_surface);

    return 0;
}


