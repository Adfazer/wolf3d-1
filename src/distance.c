#include "../includes/wolf3d.h"

int is_angle(float angle, float rad)
{
	//printf("%f\n", fabsf(cosf(angle) - cosf(rad)));
	return fabsf(cosf(angle) - cosf(rad)) < KLUDGE;
}

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
		player->distance[count_distance] = other_dummy(temp_i); //t_distance_dummy(temp_i);// dist_to_wall(temp_i);
        player->distance[count_distance].dist *= cosf(cos_agle);

		cos_agle -= player->step; // косинус используемый для домнажения на длину против эффекта аквариума берем по модулю т.к. в 2 стороны от центра обзора
		i += player->step; // следующий угол после самого правого луча
		count_distance++; // считаем количество лучей
	}
}

int		is_texture(float x, float y, char texture)
{
	return (map.map[((int)y / CUBE) * map.w + ((int)x / CUBE)] == texture);
}

static t_distance find_horizontal_intersection(float angle, char texture)
{
	t_float2	A;
	float		diffy;
	float		diffx;

	//find intersection with horizontal grid
	t_distance	inf;

	inf.dist = INT32_MAX;
	inf.tex = TEX_INF;
	if (is_angle(angle, RAD_180) || is_angle(angle, RAD_0) || is_angle(angle, RAD_360))
		return inf;


	A.y = floorf((float)p.y / CUBE) * CUBE;
	A.y = angle > RAD_0 && angle < RAD_180 ? A.y - 1: A.y + CUBE;
	A.x = p.x + (p.y - A.y) / tanf(angle);
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
	
	while (A.y > -1 && A.y < H && A.x > -1 && A.x < W)
	{
		if (ft_strchr(WALLSET, map.map[((int)A.y / CUBE) * map.w + ((int)A.x / CUBE)]))
		{
			if (angle > RAD_0 && angle < RAD_180)
				A.y++;
			if (fabsf(p.y - A.y) < KLUDGE)
				return inf;
			// if ((angle > RAD_0 && angle < RAD_180) && ((int)A.y % 64 == 0))
			// 	A.y--;
			// return (sqrtf(powf((p.x - A.x), 2) + powf((p.y - A.y), 2)));
			t_distance dist;
			dist.tex = map.map[((int)A.y / CUBE) * map.w + ((int)A.x / CUBE)];
			if (sinf(angle) > KLUDGE)
			{
				dist.dist = fabsf((p.y - A.y) / sinf(angle));
			}
			else
				dist.dist = fabsf((p.x - A.x) / cosf(angle));
			return (dist);

				/*
			else
			{
				return (fabsf((p.x - A.x) / cosf(angle)));
			}
			*/
			
		}
		A.x += diffx;
		A.y += diffy;
	}
	return inf;
}

static t_distance find_vertical_intersection(float angle, char texture)
{
	t_float2	B;
	float		diffy;
	float		diffx;
	t_distance	inf;

	inf.dist = INT32_MAX;
	inf.tex = TEX_INF;
	if (is_angle(angle, RAD_90) || is_angle(angle, RAD_270))
		return inf;

	B.x = floorf((float)p.x / CUBE) * CUBE;
	B.x = angle > RAD_270 || angle < RAD_90 ? B.x + CUBE : B.x - 1;
	B.y = p.y + (p.x - B.x) * tanf(angle);
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
	
	while (B.y >-1  && B.y < H && B.x > -1 && B.x < W)
	{
		if (ft_strchr(WALLSET, map.map[((int)B.y / CUBE) * map.w + ((int)B.x / CUBE)]))
		{
			if (angle < RAD_270 && angle > RAD_90)
				B.x++;
			if (fabsf(p.x - B.x) < KLUDGE)
				return inf;
			// if ((angle < RAD_270 && angle > RAD_90) && ((int)B.x % 64 == 0))
			// 	B.x--;
			// return (sqrtf(powf((p.x - B.x), 2) + powf((p.y - B.y), 2)));
			t_distance dist;
			dist.dist = fabsf((p.x - B.x) / cosf(angle));
			dist.tex = map.map[((int)B.y / CUBE) * map.w + ((int)B.x / CUBE)];
			return dist;
			// return (fabsf((p.y - B.y) / sinf(angle))); 
		}
		B.x += diffx;
		B.y += diffy;
	}
	return inf;
}

t_distance	t_distance_dummy(float angle)
{
	
	float	x_step;
	float	y_step;
	int		max_;
	float	x;
	float	y;

	t_distance dist;
	dist.dist = 0;
	dist.dist = TEX_FLOOR;
	float y1 = -(p.view_dist * sin(angle)); // игрек координата конца луча
	float x1 = p.view_dist * cos(angle); // икс координа конца луча
	x = p.x;
	y = p.y;
	x_step = x1;
	y_step = y1;
	y1 = y + y1;
	x1 = x + x1;
	
	max_ = fmaxf(fabs(x_step), fabs(y_step));
	x_step /= max_;
	y_step /= max_;
	int counter = 0;
	#include <stdio.h>
	//printf("%f %f\n",x_step, y_step);
	while ((int)(x - x1) || (int)(y - y1))
	{
		if (ft_strchr(WALLSET, map.map[(int)(y / CUBE) * map.w + (int)(x / CUBE)]))
		{
			dist.dist = sqrt(pow((p.x - x), 2) + pow((p.y - y), 2));
			dist.tex = *ft_strchr(WALLSET, map.map[(int)(y / CUBE) * map.w + (int)(x / CUBE)]);
			break;
		}
		else
		{
			
			x += x_step;
			y += y_step;
		}
		//printf("%d\n",counter++);
	}
	return dist;
}

t_distance other_dummy(float angle)
{
	float step = 0.0f;
	float x;
	float y;
	t_distance dist;

	dist.dist = p.view_dist;
	dist.tex = TEX_FLOOR;
	while (step < p.view_dist)
	{
		x = p.x + step * cosf(angle);
		y = p.y + step * sinf(angle);
		if (ft_strchr(WALLSET, map.map[(int)(y / CUBE) * map.w + (int)(x / CUBE)]))
		{
			dist.dist = step;
			dist.tex = *ft_strchr(WALLSET, map.map[(int)(y / CUBE) * map.w + (int)(x / CUBE)]);
			break ;
		}
		step += 0.05f;
	}
	return dist;
}


t_distance	dist_to_wall(float angle)
{
	return (dist_to_texture(angle, TEX_BORDER));
}

t_distance	dist_to_floor(float angle)
{
	return (dist_to_texture(angle, TEX_FLOOR));
}

t_distance dist_to_texture(float angle, char texture)
{
	t_distance h;
	t_distance v;

	v = find_vertical_intersection(angle, TEX_BORDER);
	h = find_horizontal_intersection(angle, TEX_BORDER);
	return (v.dist > h.dist ? h : v);
	
}