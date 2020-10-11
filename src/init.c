#include "../includes/wolf3d.h"

void	init_player(t_player *p, t_map *map)
{
	ft_bzero(p, sizeof(t_player));
	p->x = CUBE * 4;
	p->y = CUBE + 1;
	p->speed = 3.0;
	
	p->xmm = p->x / map->mm.x + map->mm_start.x;
	p->ymm = p->y / map->mm.y + map->mm_start.y;
	//ft_printf("%d %d %f\n", p->x, map->mm.x, p->xmm);
	//ft_printf("%d %d\n", p->xmm,  p->ymm);
	p->fov = RAD_60;
	p->dir = RAD_270;
	p->size = 20;
	p->dist_to_canvas = (W / 2) / tan(RAD_60 / 2);
	p->step = p->fov / W;
	p->view_dist = 512.0f;
	p->sides = 1;
	p->music_flag = 0;
	p->fps = 1;
	// p->visibility = 512.0f;
}

