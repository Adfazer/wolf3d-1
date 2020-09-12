#include "wolf3d.h"


void debug_print_map(t_map *map)
{
	if (debug)
		ft_printf("%d W %d H\n", map->h, map->w);
}