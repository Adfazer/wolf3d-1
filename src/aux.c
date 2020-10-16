#include "wolf3d.h"

int	add_arc(float *arc, float to_add)
{
	*arc += to_add;
	
	if (*arc < 0)
		*arc += RAD_360;
	else if (*arc >= RAD_360)
		*arc -= RAD_360;
	return 0;
}

int	add_floor_offset(int *offset, int to_add)
{
	*offset += to_add;
	if (*offset < 0)
		*offset += CUBE;
	else if (*offset >= CUBE)
		*offset -= CUBE;
	return 0;
}

int	max(int a, int b)
{
	return (a > b ? a : b);
}

int is_angle(float angle, float rad)
{
	return fabsf(cosf(angle) - cosf(rad)) < KLUDGE;
}

int	float_is_equal(float a, float b)
{
	return fabsf(a - b) < KLUDGE;
}

int		is_texture(t_map *map, int x, int y, char texture)
{
	return (map->map[(y / CUBE) * map->w + (x / CUBE)] == texture);
}
