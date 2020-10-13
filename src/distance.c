#include "../includes/wolf3d.h"

void    all_get_distance(t_wolf *wolf)
{
	float			i;
    int             count_distance;
    float         	cos_agle;
	float			temp_i;
	
	i = wolf->player->dir;
	i = wolf->player->dir - (wolf->player->fov / 2);
	count_distance = 0;
	cos_agle = wolf->player->fov / 2;
	while (i <= wolf->player->dir + (wolf->player->fov / 2))
	{
		temp_i = i;
		if (temp_i > RAD_360)
			temp_i -= RAD_360;
		if (temp_i < RAD_0)
			temp_i += RAD_360;
		wolf->player->distance[count_distance] = dist_to_wall(wolf, temp_i);
        wolf->player->distance[count_distance].dist *= cosf(cos_agle);
		cos_agle -= wolf->player->step;
		i += wolf->player->step;
		count_distance++;
	}
}

t_distance	dist_to_wall(t_wolf *wolf, float angle)
{
	return (dist_to_texture(wolf, angle, TEX_BORDER));
}

t_distance	dist_to_floor(t_wolf *wolf, float angle)
{
	return (dist_to_texture(wolf, angle, TEX_FLOOR));
}

t_distance dist_to_texture(t_wolf *wolf, float angle, char texture)
{
	t_distance h;
	t_distance v;

	v = find_vertical_intersection(wolf, angle, TEX_BORDER);
	h = find_horizontal_intersection(wolf, angle);
	return (v.dist > h.dist ? h : v);
	
}