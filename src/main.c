#include "../includes/wolf3d.h"

t_point	dot(int x, int y)
{
	t_point	new;

	new.x = x;
	new.y = y;
	return (new);
}

int	main()
{
	init_map(&map);
	//init_tabs();
	//load_textures(surface);
	init_player(&p, &map);
	init_sdl(&map, &p);
	return (0);
}