#include "../includes/wolf3d.h"

void    guns_shot(SDL_Surface *screen, int flag)
{
	SDL_Surface *image;
	SDL_Rect imgLocation = { 192, 448, 0, 0 };
	
	// imgLocation = { 192, 448, 0, 0 };
	flag == 1 ? image = IMG_Load("textures/guns-1.bmp"): 0;
	flag == 2 ? image = IMG_Load("textures/guns-2.bmp"): 0;
	flag == 3 ? image = IMG_Load("textures/guns-3.bmp"): 0;
	flag == 4 ? image = IMG_Load("textures/guns-4.bmp"): 0;
	flag == 5 ? image = IMG_Load("textures/guns-5.bmp"): 0;
	if (flag == 2)
	{
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		Mix_Music *music = Mix_LoadMUS("music/01664_q6IhiXXL.mp3");
		if (!music)
		{
			ft_putendl(Mix_GetError());
			exit(0);
		}
		Mix_Volume(0, 32);
		Mix_PlayMusic(music, -1);
		Mix_VolumeMusic(5);
	}
	SDL_BlitSurface(image, NULL, screen, &imgLocation);
}