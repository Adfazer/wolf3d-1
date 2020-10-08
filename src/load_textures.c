#include "../includes/wolf3d.h"

void	copy_surface(SDL_Surface *dest, SDL_Surface *source)
{

}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

switch (bpp)
{
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
      }
}


int load_textures(t_sdl *sdl)
{
	SDL_Surface *tex;
	//arr - массив с текстурами		
	//t_img **arr = (t_img **)malloc(sizeof(t_img *) * 8 *  32);
	if (!(tex = SDL_LoadBMP(TEXTURE_PATH)))
		printf("%s\n", SDL_GetError());
	//sdl->textures = SDL_ConvertSurfaceFormat(tex, SDL_PIXELFORMAT_ABGR8888, 0);
	//sdl->bytes_texture = (unsigned char*)sdl->textures->pixels;

	sdl->arr = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * tex->w / CUBE * tex->h / CUBE);
	SDL_Surface **arr = sdl->arr;
	 

	int		i;
	int		j;
	int		a;

	i = -1;
	a = -1;
	
	while (++a < tex->w * tex->h)
	{
		arr[a] = SDL_CreateRGBSurface(0, CUBE, CUBE, 32, RMASK, GMASK, BMASK, AMASK);
		int x = a % 8;
		int y = a / 8;
		for (int i = 0; i < 64; i+=1)
		{
			for (int j = 0; j < 64; j++)
			{	
				set_pixel(
					arr[a],
					dot(j, i),
					0x00ff00);
					//getpixel(surface, j + x * 64, i * surface->w + y * surface->w * 64));
			}
		}
	}

	SDL_FreeSurface(tex);
	
	return 0;
}