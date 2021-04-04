#include "saturation.h"
#include "../import/import.h"

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include <stdio.h>
#include <math.h>

void saturation_level(SDL_Surface *img, char level)
{
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int w, h;
  w = img -> w; 
  h = img -> h;
 
  
  for(int i = 0; i < w; i++)
    {
      for(int j = 0; j < h; j++)
        {
	  pixel = getpixel(img, i, j);
	  SDL_GetRGB(pixel, img->format, &r, &g, &b);
	  
	  if (level == '0')//negative saturation
	    {
	      r = r*0.3 + g*0.59 + b*0.11;
	      g = r*0.3 + g*0.59 + b*0.11;
	      b = r*0.3 + g*0.59 + b*0.11;
	    }
	  
	  if (level == '1')//medium saturation
	    {
	      if (r > b && r > g && r < 256)
		r += (255 - r)*0.11;
	      if (b > r && b > g && b < 256)
		b += (255 - b)*0.11;
	      if (g > r && g > b && g < 256)
		g += (255 - g)*0.11;
	    }
	  
	  if (level == '2')//high saturation
	    {
	      if (r > b && r > g && r < 256)
		r += (255 - r)*0.2;
	      if (b > r && b > g && b < 256)
		b += (255 - b)*0.2;
	      if (g > r && g > b && g < 256)
		g += (255 - g)*0.2;
	    }
	  
	  pixel = SDL_MapRGB(img->format, r, g, b);
	  putpixel(img, i, j, pixel);
	}
	  
    }

}
