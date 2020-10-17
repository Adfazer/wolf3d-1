#include "../includes/wolf3d.h"

void	music(t_bonus *bon)
{
	Mix_Volume(0, 32);
    if (bon->music_flag == 1)
	    Mix_PlayMusic(bon->music, -1);
	Mix_VolumeMusic(5);
}