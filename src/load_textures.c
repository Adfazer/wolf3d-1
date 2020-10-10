#include "../includes/wolf3d.h"


void set_pixel(SDL_Surface *surface, t_point point, Uint32 pixel)
{
  Uint32 *target_pixel = (Uint32 *)((Uint8 *)surface->pixels + point.y * surface->pitch
  	 + point.x * sizeof *target_pixel);
  *target_pixel = pixel;
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	return *(Uint32 *)p;
}

int	get_color(Uint32 pixel, SDL_PixelFormat *format)
{
	SDL_Color rgb;

	SDL_GetRGB(pixel, format, &rgb.r, &rgb.g, &rgb.b);
	return color_to_hex(rgb.r, rgb.g, rgb.b);
}

int load_textures(t_wolf *wolf, t_sdl *sdl)
{
	SDL_Surface *tex;
	//arr - массив с текстурами		
	//t_img **arr = (t_img **)malloc(sizeof(t_img *) * 8 *  32);
	if (!(tex = SDL_LoadBMP(TEXTURE_PATH)))
		printf("%s\n", SDL_GetError());
	sdl->textures = tex;	
	//sdl->textures = SDL_ConvertSurfaceFormat(tex, SDL_PIXELFORMAT_ABGR8888, 0);
	sdl->bytes_texture = (unsigned char*)sdl->textures->pixels;
	
	return 0;
}