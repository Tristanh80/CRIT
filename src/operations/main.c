#include "../import/import.h"
#include "grey.h"
#include "filters.h"
#include "blur.h"
#include "border.h"
#include "rotate.h"
#include "sym.h"
#include "saturation.h"
#include "testgd.h"

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include <string.h>
#include <gd.h>

void usage(void)
{
    printf("Usage:\n");
    printf("./main 1 for greyscale\n");
    printf("./main 2 for monochromatic\n");
    printf("./main 3 for red\n");
    printf("./main 4 for green\n");
    printf("./main 5 for blue\n");
    printf("./main 6 for blur\n");
    printf("./main 7 for border\n");
    printf("./main 8 for symh\n");
    printf("./main 9 for symv\n");
    printf("./main 10 for saturation\n");
}



int main(int argc, char* argv[])
{
    FILE *fd=NULL;
    gdImagePtr img = gdImageCreateFromFile("chromatic_circle.jpg");
    char *path = "testimg.png";
    //negate(img, fd, path);
    //contrast(img, fd, path, -50);
    emboss(img, fd, path);

    /*SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    void init_sdl();

    if(argc != 2)
    {
        usage();
        return EXIT_FAILURE;
    }
    unsigned long param = strtoul(argv[1],NULL,10);
    if(param<1 || param>11)
    {
        usage();
        return EXIT_FAILURE;
    }
    if(param == 1)
    {
        image_surface = load_image("my_image.jpg");
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        greyscale(image_surface);
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        SDL_FreeSurface(image_surface);
        SDL_FreeSurface(screen_surface);
    }
    if(param == 2)
    {
        image_surface = load_image("my_image.jpg");
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        monochromatic(image_surface);
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        SDL_FreeSurface(image_surface);
        SDL_FreeSurface(screen_surface);
    }
    if(param == 3)
    {
        image_surface = load_image("my_image.jpg");
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        red(image_surface);
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        SDL_FreeSurface(image_surface);
        SDL_FreeSurface(screen_surface);
    }
    if(param == 4)
    {
        image_surface = load_image("my_image.jpg");
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        green(image_surface);
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        SDL_FreeSurface(image_surface);
        SDL_FreeSurface(screen_surface);
    }
    if(param == 5)
    {
        image_surface = load_image("my_image.jpg");
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        blue(image_surface);
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        SDL_FreeSurface(image_surface);
        SDL_FreeSurface(screen_surface);
    }
    if(param == 6)
    {
        image_surface = load_image("my_image.jpg");
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        blur(image_surface,10);
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        SDL_FreeSurface(image_surface);
        SDL_FreeSurface(screen_surface);
    }
    if(param == 7)
    {
        image_surface = load_image("my_image.jpg");
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        border(image_surface, 10);
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        SDL_FreeSurface(image_surface);
        SDL_FreeSurface(screen_surface);
    }
    if(param == 8)
    {
        image_surface = load_image("my_image.jpg");
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        symh(image_surface);
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        SDL_FreeSurface(image_surface);
        SDL_FreeSurface(screen_surface);
    }
    if(param == 9)
    {
        image_surface = load_image("my_image.jpg");
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        symv(image_surface);
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        SDL_FreeSurface(image_surface);
        SDL_FreeSurface(screen_surface);
    }
    if(param == 10)
    {
        image_surface = load_image("my_image.jpg");
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        saturation_level(image_surface,'1');
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        SDL_FreeSurface(image_surface);
        SDL_FreeSurface(screen_surface);
    }

    if(param == 11)
    {
        image_surface = load_image("my_image.jpg");
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        dashborder(image_surface,10 ,20);
        screen_surface = display_image(image_surface);
        wait_for_keypressed();
        SDL_FreeSurface(image_surface);
        SDL_FreeSurface(screen_surface);
    }

*/

    return 0;

}


