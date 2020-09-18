#include "wolf3d.h"

float arcToRad(float angle)
{
	return ((angle * M_PI) / a.a180);
}

int		color_to_hex(int r, int g, int b)
{	
	return (r << 16) | (g << 8) | b;
}

int	add_arc(float *arc, float to_add)
{
	*arc += to_add;
	if (*arc < 0)
		*arc += 360;
	else if (*arc >= 360)
		*arc -= 360;
	return (*arc);
}