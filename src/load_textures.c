#include "../includes/wolf3d.h"


void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  Uint32 *target_pixel = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch
  	 + x * sizeof *target_pixel);
  *target_pixel = pixel;
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
	return *(Uint32 *)p;
}
