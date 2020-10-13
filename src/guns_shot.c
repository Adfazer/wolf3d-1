#include "../includes/wolf3d.h"

void    guns_shot(SDL_Surface *screen, int flag, t_bonus *bon)
{
	if (flag == 2)
	{
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		Mix_Chunk *music = Mix_LoadWAV("music/01664_q6IhiXXL.wav");
		if (!music)
		{
			ft_putendl(Mix_GetError());
			exit(0);
		}
		Mix_Volume(0, 32);
		Mix_PlayChannel(1, music, 0);
		Mix_VolumeMusic(5);
	}
	flag == 1 ? SDL_BlitScaled(bon->image_1, NULL, screen, &bon->imgLocation): 0;
	flag == 2 ? SDL_BlitScaled(bon->image_2, NULL, screen, &bon->imgLocation): 0;
	flag == 3 ? SDL_BlitScaled(bon->image_3, NULL, screen, &bon->imgLocation): 0;
	flag == 4 ? SDL_BlitScaled(bon->image_4, NULL, screen, &bon->imgLocation): 0;
	flag == 5 ? SDL_BlitScaled(bon->image_5, NULL, screen, &bon->imgLocation): 0;
}

void	render_shot(t_wolf *wolf, SDL_Surface *surface, int *flag_guns, int start_guns)
{
	if (wolf->bon->guns_fire || *flag_guns != 0)
	{
		wolf->bon->guns_fire = 0;
		if (!start_guns)
		{
			*flag_guns++;
			start_guns = SDL_GetTicks();
		}
		if (start_guns + 200 < SDL_GetTicks())
		{
			*flag_guns++;
			start_guns = SDL_GetTicks();
		}
		guns_shot(surface, *flag_guns, wolf->bon);
		// flag_guns == 5 ? Mix_HaltMusic(): 0;
		*flag_guns == 5 ? *flag_guns = 0: 0;
	}
	else
		guns_shot(surface, 1, wolf->bon);
}