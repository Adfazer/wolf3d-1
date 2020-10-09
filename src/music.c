#include "../includes/wolf3d.h"

void	music(t_player *player)
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	player->music = Mix_LoadMUS("music/Oto Kapanadze - Mystic Mountain.mp3");
	if (!player->music)
	{
		ft_putendl(Mix_GetError());
		exit(0);
	}
	Mix_Volume(0, 32);
    if (player->music_flag == 1)
	    Mix_PlayMusic(player->music, -1);
	Mix_VolumeMusic(5);
}