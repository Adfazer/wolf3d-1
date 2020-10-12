#include "../includes/wolf3d.h"

void	init_player(t_player *p, t_map *map)
{
	ft_bzero(p, sizeof(t_player));
	p->size = 10;
	p->x = CUBE * (map->player_start % map->w) + p->size;
	p->y = CUBE * (map->player_start / map->w) + p->size;
	p->speed = 3.0;
	
	p->fov = RAD_60;
	p->dir = RAD_270;
	p->size = 10;
	p->dist_to_canvas = (W / 2) / tan(RAD_60 / 2);
	p->step = p->fov / W;
	p->view_dist = 512.0f;
	p->sides = 1;
	p->music_flag = 0;
	p->fps = 1;
	// p->visibility = 512.0f;
}

