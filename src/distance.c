#include "../includes/wolf3d.h"

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
        player->distance[count_distance] = find_wall(temp_i) * cosf(cos_agle);
		cos_agle -= step; // косинус используемый для домнажения на длину против эффекта аквариума берем по модулю т.к. в 2 стороны от центра обзора
		i += step; // следующий угол после самого правого луча
		count_distance++; // считаем количество лучей
	}
}