#include "../includes/wolf3d.h"

t_point	dot(int x, int y)
{
	t_point	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_wolf		*t_wolf_new(void)
{
	t_wolf	*new;

	!(new = (t_wolf *)malloc(sizeof(t_wolf))) ? error(new, ERR_MALLOC) : 0;
	!(new->map = (t_map *)malloc(sizeof(t_map))) ? error(new, ERR_MALLOC) : 0;
	if (!(new->player = (t_player *)malloc(sizeof(t_player))))
		error(new, ERR_MALLOC);
	if (!(new->surface = (SDL_Surface *)malloc(sizeof(SDL_Surface))))
		error(new, ERR_MALLOC);
	if (!(new->sdl = (t_sdl *)malloc(sizeof(t_sdl))))
		error(new, ERR_MALLOC);
	if (!(new->bon = (t_bonus *)malloc(sizeof(t_bonus))))
		error(new, ERR_MALLOC);
	return new;
}

void		validate_const(t_wolf *wolf)
{
	if (H > W)
		error(wolf, ERR_INV_H);
}

int			main(int a, char **b)
{
	t_wolf	*wolf;

	wolf = NULL;
	validate_const(wolf);
	a != 2 ? error(wolf, ERR_USAGE) : 0;
	SDL_Init(SDL_INIT_EVERYTHING) != 0 ? error(wolf, SDL_GetError()) : 0;
	TTF_Init() != 0 ? error(wolf, SDL_GetError()) : 0;
	wolf = t_wolf_new();
	map_init(wolf, b[1]);
	player_init(wolf->player, wolf->map);
	bonus_init(wolf->bon);
	music(wolf->bon);
	init_tex_arr(wolf);
	wolf_loop(wolf);
	return (0);
}