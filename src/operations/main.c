#include "../import/import.h"
#include "grey.h"
#include "filters.h"
#include "blur.h"
#include "border.h"
#include "rotate.h"
#include "sym.h"
#include "saturation.h"

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include <string.h>


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

        image_surface = rotate(image_surface, 'r');
        //saturation_level(image_surface, '2');
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



    else if(argc == 3)
    {
        wait_for_keypressed();
        if (strcmp(argv[1], "filter") == 0)
        {
            char color = *argv[2];
            filter(image_surface, color);
            screen_surface = display_image(image_surface);
        }
        if (strcmp(argv[1], "saturation") == 0)
        {
            char level = *argv[2];
            saturation_level(image_surface, level);
            screen_surface = display_image(image_surface);
        }
        wait_for_keypressed();


    }

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

    return 0;

}


