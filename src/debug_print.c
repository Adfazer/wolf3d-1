#include "wolf3d.h"

void debug_map(t_map *map)
{
	if (DEBUG)
	{
		ft_printf("%s MAP INFO %s\n", C_YEL, C_NRM);
		ft_printf("%d map.w | %d map.h", map->w, map->h);
	}
}

void debug_player(t_player *p)
{
	if (DEBUG)
	{
		ft_printf("%s PLAYER INFO %s\n", C_GRN, C_NRM);
		ft_printf("\t%d p.x | %d p.y\n", p->x, p->y);
		ft_printf("\t%d p.xmm | %d p.ymm\n", p->xmm, p->ymm);
		ft_printf("\t%d p.dir  | %d p.fov\n", p->dir, p->fov);
	}
}

