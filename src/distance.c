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
    float           cos_agle;
    float           step;
	float			temp_i;
	
	i = player->dir - (player->fov / 2); // угол самого правого луча
	count_distance = 0; // переменная [номер] луча
	cos_agle = player->fov / 2; // самый большой крайний косинус
	step = player->fov / W; // шаг смещения угла(косинуса) и угла самого правого луча от ширины экрана
	while (i <= player->dir + (player->fov / 2)) // идем по всем промежуточным углам области обзора 
	{
		temp_i = i;
		if (temp_i > RAD_360)
			temp_i -= RAD_360;
		if (temp_i < RAD_0)
			temp_i += RAD_360;
        player->distance[count_distance] = dist_to_wall(temp_i) * cosf(cos_agle);
		cos_agle -= step; // косинус используемый для домнажения на длину против эффекта аквариума берем по модулю т.к. в 2 стороны от центра обзора
		i += step; // следующий угол после самого правого луча
		count_distance++; // считаем количество лучей
	}
}

int		is_texture(float x, float y, char texture)
{
	return (map.map[((int)y / CUBE) * map.w + ((int)x / CUBE)] == texture);
}

static double find_horizontal_intersection(double angle, char texture)
{
	t_float2	A;
	double		diffy;
	double		diffx;

	//find intersection with horizontal grid
	if (is_angle(angle, RAD_180) || is_angle(angle, RAD_0) || is_angle(angle, RAD_360))
		return INT32_MAX;

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
	
	while (A.y >= 0 && A.y < H && A.x >= 0 && A.x < W)
	{
		if (map.map[((int)A.y / CUBE) * map.w + ((int)A.x / CUBE)] == texture)
		{
			if (angle > RAD_0 && angle < RAD_180)
				A.y++;
			if (fabsf(p.y - A.y) < KLUDGE)
				return INT32_MAX;
			// if ((angle > RAD_0 && angle < RAD_180) && ((int)A.y % 64 == 0))
			// 	A.y--;
			// return (sqrtf(powf((p.x - A.x), 2) + powf((p.y - A.y), 2)));
			return (fabsf((p.y - A.y) / sinf(angle)));
			// return (fabsf((p.x - A.x) / cosf(angle)));
		}
		A.x += diffx;
		A.y += diffy;
	}
	return INT32_MAX;
}

static double find_vertical_intersection(double angle, char texture)
{
	t_float2	B;
	double		diffy;
	double		diffx;

	if (is_angle(angle, RAD_90) || is_angle(angle, RAD_270))
		return INT32_MAX;

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
	
	while (B.y >= 0 && B.y < H && B.x >= 0 && B.x < W)
	{
		if (map.map[((int)B.y / CUBE) * map.w + ((int)B.x / CUBE)] == texture)
		{
			if (angle < RAD_270 && angle > RAD_90)
				B.x++;
			if (fabsf(p.x - B.x) < KLUDGE)
				return INT32_MAX;
			// if ((angle < RAD_270 && angle > RAD_90) && ((int)B.x % 64 == 0))
			// 	B.x--;
			// return (sqrtf(powf((p.x - B.x), 2) + powf((p.y - B.y), 2)));
			return (fabsf((p.x - B.x) / cosf(angle)));
			// return (fabsf((p.y - B.y) / sinf(angle))); 
		}
		B.x += diffx;
		B.y += diffy;
	}
	return INT32_MAX;
}

double	dist_to_wall(double angle)
{
	return (dist_to_texture(angle, TEX_BORDER));
}

double	dist_to_floor(double angle)
{
	return (dist_to_texture(angle, TEX_FLOOR));
}

double dist_to_texture(double angle, char texture)
{
	double a = fminf(
		find_horizontal_intersection(angle, TEX_BORDER),
		find_vertical_intersection(angle, TEX_BORDER)
		);
	// ft_printf("%f\n", a);
	return a;
}