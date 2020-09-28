#include "../includes/wolf3d.h"

void    all_get_distance(t_map *map, t_player *player)
{
	float			i;
	float			y;
	float			x;
    int             count_distance;
    float           cos_agle;
    float           step;
	
	i = player->dir - (player->fov / 2); // угол самого правого луча
	count_distance = 0; // переменная [номер] луча
	cos_agle = player->fov / 2; // самый большой крайний косинус
	step = player->fov / W; // шаг смещения угла(косинуса) и угла самого правого луча от ширины экрана
	while (i <= player->dir + (player->fov / 2)) // идем по всем промежуточным углам области обзора 
	{
        y = player->visibility * sin(i); // игрек координата конца луча
        x = player->visibility * cos(i); // икс координа конца луча
        // printf("%f--x\n%f--y\n", x, y);
        player->distance[count_distance] = find_wall(i) * cos(cos_agle);
		//get_distance(map,player, -y, x, fabs(cos_agle), count_distance);
		// 
		cos_agle -= step; // косинус используемый для домнажения на длину против эффекта аквариума берем по модулю т.к. в 2 стороны от центра обзора
		i += step; // следующий угол после самого правого луча
        // ft_printf("%f--mydis\n", player->distance[count_distance]);
		count_distance++; // считаем количество лучей
	}
    // exit(0);
}

void    get_distance(t_map *map, t_player *player, float y1, float x1, float cos_agle, int count_distance)
{
    float	x_step;
	float	y_step;
	int		max_step;
	float	x;
	float	y;
    // t_point point;

	x = player->x;
	y = player->y;
	x_step = x1;
	y_step = y1;
	y1 = y + y1;
	x1 = x + x1;
	max_step = fmax(fabs(x_step), fabs(y_step));
	x_step /= max_step;
	y_step /= max_step;
	while ((int)(x - x1) || (int)(y - y1))
	{
		if (map->map[(int)y * map->w + (int)x] == TEX_BORDER)
		{
			player->distance[count_distance] = sqrt(powf((player->x - x), 2) + powf((player->y - y), 2)); // вычисление длины луча
			player->distance[count_distance] *= cos(cos_agle); // против искажений типа аквариум при вычислений длины луча
			break;
		}
		else
		{
            // int color = 255 << 16;
            // point.x = (int)x;
            // point.y = (int)y;
			player->distance[count_distance] = 0;
            // set_pixel(surface, point, color);
			// if (data->player.map_view == 1) // убрать отображение лучей 
			// 	data->img_data[(int)y * data->w + (int)x] = data->color;
			x += x_step;
			y += y_step;
		}    
	}
    // ft_printf("%f\n", player->distance[count_distance]);
}
