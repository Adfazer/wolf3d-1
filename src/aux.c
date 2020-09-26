#include "wolf3d.h"

double arcToRad(double angle)
{
	return ((angle * M_PI) / a.a180);
}

int		color_to_hex(int r, int g, int b)
{	
	return (r << 16) | (g << 8) | b;
}

int	add_arc(double *arc, double to_add)
{
	*arc += to_add;
	/*
	if (*arc < 0)
		*arc += RAD_360;
	else if (*arc >= RAD_360)
		*arc -= RAD_360;
		*/
	return (*arc);
}