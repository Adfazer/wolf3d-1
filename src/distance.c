#include "../includes/wolf3d.h"

void    all_get_distance(t_map *map, t_player *player)
{
	float			i;
    int             count_distance;
    float         	cos_agle;
	float			temp_i;
	
	i = player->dir;
	i = player->dir - (player->fov / 2); // угол самого правого луча
	count_distance = 0; // переменная [номер] луча
	cos_agle = player->fov / 2; // самый большой крайний косинус
	while (i <= player->dir + (player->fov / 2)) // идем по всем промежуточным углам области обзора 
	{
		temp_i = i;
		if (temp_i > RAD_360)
			temp_i -= RAD_360;
		if (temp_i < RAD_0)
			temp_i += RAD_360;
		player->distance[count_distance] = dist_to_wall(player, map, temp_i); //t_distance_dummy(temp_i);// dist_to_wall(temp_i);
        player->distance[count_distance].dist *= cosf(cos_agle);

		cos_agle -= player->step; // косинус используемый для домнажения на длину против эффекта аквариума берем по модулю т.к. в 2 стороны от центра обзора
		i += player->step; // следующий угол после самого правого луча
		count_distance++; // считаем количество лучей
	}
}

int		is_texture(t_map *map, int x, int y, char texture)
{
	return (map->map[(y / CUBE) * map->w + (x / CUBE)] == texture);
}

static t_distance find_horizontal_intersection(t_player *p, t_map *map, float angle, char texture)
{
	t_float2	A;
	float		diffy;
	float		diffx;
	t_distance 	dist;

	A.y = floorf((float)p->y / CUBE) * CUBE;
	A.y = angle > RAD_0 && angle < RAD_180 ? A.y/* - 1*/: A.y + CUBE;
	A.x = p->x + (p->y - A.y) / tanf(angle);
	diffx = CUBE / tanf(angle);
		
	if (angle > RAD_270 && angle < RAD_360) // 4
	{
		diffx = -diffx;
		diffy = CUBE;
	}
	else if (angle > RAD_90 && angle < RAD_180) // --1
	{
		diffx = diffx;
		diffy = -CUBE;
	}
	else if (angle > RAD_0 && angle < RAD_90) // 2
	{
		diffx = (diffx);
		diffy = -CUBE;
	}
	else/* if (angle > RAD_180 && angle < RAD_270)*/ // 3
	{
		diffx = -diffx;
		diffy = CUBE;
	}
	
	while (A.y > -1 && A.y < map->h_pix && A.x > -1 && A.x < map->w_pix)
	{
		if (angle > RAD_0 && angle < RAD_180)
		{
			if (ft_strchr(WALLSET, map->map[((int)(A.y - 1) / CUBE) * map->w + ((int)A.x / CUBE)]))
			{
			dist.dist = fabsf((p->y - A.y) / sinf(angle));
			dist.offsetx = (int)A.x % 64;
			if (p->sides)
				dist.tex = 'S';
			else
			{
				// float a;
				// dist.tex = modff(A.x / CUBE, &a);
				// https://proglib.io/p/raycasting-for-the-smallest шаг 11
				dist.tex = map->map[((int)(A.y - 1) / CUBE) * map->w + ((int)A.x / CUBE)];
			}
			return (dist);
			}
		}
		else if (ft_strchr(WALLSET, map->map[((int)A.y / CUBE) * map->w + ((int)A.x / CUBE)]))
		{
			dist.dist = fabsf((p->y - A.y) / sinf(angle));
			dist.offsetx = (int)A.x % 64;
			if (p->sides)
				dist.tex = 'N';
			else
			{
				// float b;
				// dist.tex = modff(A.x / CUBE, &b);
				// https://proglib.io/p/raycasting-for-the-smallest шаг 11
				dist.tex = map->map[((int)A.y / CUBE) * map->w + ((int)A.x / CUBE)];
			}
			return (dist);
		}
		A.x += diffx;
		A.y += diffy;
	}
	return dist;
}

static t_distance find_vertical_intersection(t_player *p, t_map *map, float angle, char texture)
{
	t_float2	B;
	float		diffy;
	float		diffx;
	t_distance	inf;
	t_distance 	dist;

	inf.dist = INT32_MAX;
	inf.tex = TEX_INF;
	// if (is_angle(angle, RAD_90) || is_angle(angle, RAD_270))
	// 	return inf;


	B.x = floorf((float)p->x / CUBE) * CUBE;
	B.x = angle > RAD_270 || angle < RAD_90 ? B.x + CUBE : B.x/* - 1*/;
	B.y = p->y + (p->x - B.x) * tanf(angle);
	diffy = CUBE * tanf(angle);

	if (angle > RAD_270 && angle < RAD_360) // 4
	{
		diffy = -diffy;
		diffx = CUBE;
	}
	else if (angle > RAD_90 && angle < RAD_180) // --1
	{
		diffy = diffy;
		diffx = -CUBE;
	}
	else if (angle > RAD_0 && angle < RAD_90) // 2
	{
		diffy = (-diffy);
		diffx = CUBE;
	}
	else/* if (angle > RAD_180 && angle < RAD_270) */// 3
	{
		diffy = diffy;
		diffx = -CUBE;		
	}
	
	while (B.y >-1  && B.y < map->h_pix && B.x > -1 && B.x < map->w_pix)
	{
		if (angle < RAD_270 && angle > RAD_90)
		{
			if (ft_strchr(WALLSET, map->map[((int)B.y / CUBE) * map->w + ((int)(B.x - 1) / CUBE)]))
			{
			dist.dist = fabsf((p->x - B.x) / cosf(angle));
			dist.offsetx = (int)B.y % 64;
			if (p->sides)
				dist.tex = 'W';
			else
			{
				// float a;
				// dist.tex = modff(B.y / CUBE, &a);
				// https://proglib.io/p/raycasting-for-the-smallest шаг 11
				// нужно помимо меры передавать с каким блоком столкнулись
				dist.tex = map->map[((int)B.y / CUBE) * map->w + ((int)(B.x - 1) / CUBE)];
			}
			return dist;
			}
		}
		else if (ft_strchr(WALLSET, map->map[((int)B.y / CUBE) * map->w + ((int)B.x / CUBE)]))
		{
			dist.dist = fabsf((p->x - B.x) / cosf(angle));
			dist.offsetx = (int)B.y % 64;
			if (p->sides)
				dist.tex = 'E';
			else
			{
				// float b;
				// dist.tex = modff(B.y / CUBE, &b);
				// https://proglib.io/p/raycasting-for-the-smallest шаг 11
				dist.tex = map->map[((int)B.y / CUBE) * map->w + ((int)B.x / CUBE)];
			}
			return dist;
		}
		B.x += diffx;
		B.y += diffy;
	}
	return inf;
}

t_distance	dist_to_wall(t_player *p, t_map *map, float angle)
{
	return (dist_to_texture(p, map, angle, TEX_BORDER));
}

t_distance	dist_to_floor(t_player *p, t_map *map, float angle)
{
	return (dist_to_texture(p, map, angle, TEX_FLOOR));
}

t_distance dist_to_texture(t_player *p, t_map *map, float angle, char texture)
{
	t_distance h;
	t_distance v;

	v = find_vertical_intersection(p, map, angle, TEX_BORDER);
	h = find_horizontal_intersection(p, map, angle, TEX_BORDER);
	return (v.dist > h.dist ? h : v);
	
}