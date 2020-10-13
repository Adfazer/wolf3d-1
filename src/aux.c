#include "wolf3d.h"

int		color_to_hex(int r, int g, int b)
{	
	return (r << 16) | (g << 8) | b;
}

int	add_arc(float *arc, float to_add)
{
	*arc += to_add;
	
	if (*arc < 0)
		*arc += RAD_360;
	else if (*arc >= RAD_360)
		*arc -= RAD_360;
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