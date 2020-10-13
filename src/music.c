#include "../includes/wolf3d.h"

void	music(t_bonus *bon)
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	bon->music = Mix_LoadMUS("music/Oto Kapanadze - Mystic Mountain.mp3");
	if (!bon->music)
	{
		ft_putendl(Mix_GetError());
		exit(0);
	}
	Mix_Volume(0, 32);
    if (bon->music_flag == 1)
	    Mix_PlayMusic(bon->music, -1);
	Mix_VolumeMusic(5);
}