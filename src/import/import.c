#include "import.h"


#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>

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


static inline Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y)
{
 int bpp = surf -> format -> BytesPerPixel;
 return (Uint8*)surf -> pixels + y * surf -> pitch + x * bpp;
}


Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y)
{
 Uint8 *p = pixelref(surface, x, y);
 switch(surface -> format -> BytesPerPixel) {
 case 1:
   return *p;
 case 2:
   return *(Uint16 *)p;
 case 3:
   if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
     return p[0] << 16 | p[1] << 8 | p[2];
   else
     return p[0] | p[1] << 8 | p[2] << 16;
 case 4:
   return *(Uint32 *)p;
 }
 return 0;
}

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{
 Uint8 *p = pixelref(surface, x, y);
 switch(surface -> format -> BytesPerPixel) {
 case 1:
   *p = pixel;
   break;
 case 2:
   *(Uint16 *)p = pixel;
   break;
 case 3:
   if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
     p[0] = (pixel >> 16) & 0xff;
     p[1] = (pixel >> 8) & 0xff;
     p[2] = pixel & 0xff;
   } else {
     p[0] = pixel & 0xff;
     p[1] = (pixel >> 8) & 0xff;
     p[2] = (pixel >> 16) & 0xff;
   }
   break;
 case 4:
   *(Uint32 *)p = pixel;
   break;
 }
}



SDL_Surface* copy_image(SDL_Surface *img)
{
  Uint32 pixel;
  SDL_Surface* copy;
  copy = SDL_CreateRGBSurface(SDL_HWSURFACE,
                              img -> w,
                              img -> h,
                              img -> format -> BitsPerPixel,0,0,0,0);
  for(int i = 0; i < img -> w; i++)
  {
    for(int j = 0;j < img -> h; j++)
    {
      pixel = getpixel(img, i, j);
      putpixel(copy, i, j, pixel);
    }
  }
  return(copy);
}


void greyscale(SDL_Surface *img)
{
   /* Variables */
   Uint32 pixel;
   Uint8 r;
   Uint8 g;
   Uint8 b;
   float coef_r;
   float coef_g;
   float coef_b;
   int w;
   int h;
   w = img -> w;
   h = img -> h;

  /* Iterate on each pixels and greyscale */
  for(int i = 0; i < w; i++)
  {
    for(int j = 0; j < h; j++)
    {
      /* Apply luminance on r g b */
      pixel = getpixel(img, i, j);
      SDL_GetRGB(pixel, img->format, &r, &g, &b);
      coef_r = r * 0.3;
      coef_g = g * 0.59;
      coef_b = b * 0.11;
      r = coef_r + coef_g + coef_b;
      g = coef_r + coef_g + coef_b;
      b = coef_r + coef_g + coef_b;
      pixel = SDL_MapRGB(img->format, r, g, b);
      putpixel(img,i,j,pixel);
    }
  }
}



int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    void init_sdl();

    image_surface = load_image("my_image.jpg");
    screen_surface = display_image(image_surface);

    wait_for_keypressed();

    greyscale(image_surface);
    //screen_surface = display_image(image_surface);

    //wait_for_keypressed();

    SDL_Surface *img2 = copy_image(image_surface);

    screen_surface = display_image(img2);

    wait_for_keypressed();

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

    return 0;
}
