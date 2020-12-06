#include "../includes/wolf3d.h"

// int		score_monster(t_wolf *wolf, t_coin *coin)
// {
// 	float	x;
// 	float	y;
// 	int		flag;

// 	flag = 0;
// 	if (coin->dist < 20 || wolf->bon->penetration_flag == 1)
// 	{
// 		Mix_Volume(0, 32);
// 		Mix_PlayChannel(2, wolf->bon->music_coin, 0);
// 		Mix_VolumeMusic(5);
// 		wolf->bon->score_coin++;
// 		wolf->bon->penetration_flag = 0;
// 		while (flag != 1)
// 		{
// 			y = rand() % wolf->map->h;
// 			x = rand() % wolf->map->w;
// 			if (wolf->map->map[(int)(y * wolf->map->w + x)] == TEX_FLOOR)
// 			{
// 				wolf->bon->monster_pos.x = (x + 0.5) * CUBE;
// 				wolf->bon->monster_pos.y = (y + 0.5) * CUBE;
// 				flag = 1;
// 			}
// 		}
// 	}
// 	return (0);
// }

int		search_angle_monster(t_wolf *wolf, int i)
{
	wolf->monster->data[i].dist = sqrtf(powf((wolf->monster->monster_pos[i].x - wolf->player->x), 2)
		+ powf((wolf->monster->monster_pos[i].y - wolf->player->y), 2));
	// if (score_monster(wolf, coin))
	// 	return (1);
	if (wolf->monster->monster_pos[i].x - wolf->player->x > 0
		&& wolf->monster->monster_pos[i].y - wolf->player->y < 0)
		wolf->monster->data[i].angle = asin((wolf->player->y - wolf->monster->monster_pos[i].y)
			/ wolf->monster->data[i].dist);
	else if (wolf->monster->monster_pos[i].x - wolf->player->x < 0
		&& wolf->monster->monster_pos[i].y - wolf->player->y < 0)
		wolf->monster->data[i].angle = asin((wolf->monster->monster_pos[i].y - wolf->player->y)
			/ wolf->monster->data[i].dist) + RAD_180;
	else if (wolf->monster->monster_pos[i].x - wolf->player->x < 0
		&& wolf->monster->monster_pos[i].y - wolf->player->y > 0)
		wolf->monster->data[i].angle = asin((wolf->monster->monster_pos[i].y - wolf->player->y)
			/ wolf->monster->data[i].dist) + RAD_180;
	else if (wolf->monster->monster_pos[i].x - wolf->player->x > 0
		&& wolf->monster->monster_pos[i].y - wolf->player->y > 0)
		wolf->monster->data[i].angle = asin((wolf->player->y - wolf->monster->monster_pos[i].y)
			/ wolf->monster->data[i].dist) + RAD_360;
	return (0);
}

void    wall_check_monster(t_wolf *wolf, int i)
{
	wolf->monster->data[i].i = (int)((W / wolf->player->fov) * ( wolf->monster->data[i].temp_3)
		- ((W / 32) * (wolf->player->dist_to_canvas /  wolf->monster->data[i].dist)) / 2);
	while ( wolf->monster->data[i].i < (W / wolf->player->fov) * ( wolf->monster->data[i].temp_3)
		+ ((W / 32) * (wolf->player->dist_to_canvas /  wolf->monster->data[i].dist)) / 2)
	{
		if ( wolf->monster->data[i].i > 0 &&  wolf->monster->data[i].i <= W)
		{
			if ( wolf->monster->data[i].dist < wolf->player->distance[W -  wolf->monster->data[i].i]->dist
				/ cosf(wolf->player->fov / 2))
			{
				if (wolf->monster->data[i].flag_1 == 0)
				{
					wolf->monster->data[i].flag_i = wolf->monster->data[i].i;
					wolf->monster->data[i].flag_1 = wolf->monster->data[i].count;
				}
			}
			else if (wolf->monster->data[i].flag_2 == 0 && wolf->monster->data[i].flag_1 != 0)
				wolf->monster->data[i].flag_2 = wolf->monster->data[i].count;
		}
		wolf->monster->data[i].i++;
		wolf->monster->data[i].count++;
	}
	wolf->monster->data[i].count--;
	if (wolf->monster->data[i].flag_1 != 0 && (wolf->monster->data[i].flag_2 == 0 || wolf->monster->data[i].flag_2 == 1))
		wolf->monster->data[i].flag_2 = wolf->monster->data[i].count;
}

void    through_zero_monster(t_wolf *wolf, int i)
{
   wolf->monster->data[i].temp_1 = wolf->player->dir - wolf->player->fov / 2;
	if (wolf->player->dir - wolf->player->fov / 2 < RAD_0)
		wolf->monster->data[i].temp_1 = wolf->player->dir + RAD_360 - wolf->player->fov / 2;
	wolf->monster->data[i].temp_2 = wolf->monster->data[i].angle - (wolf->monster->data[i].temp_1);
	if (wolf->monster->data[i].temp_2 < RAD_0)
		wolf->monster->data[i].temp_2 = wolf->monster->data[i].angle + RAD_360 - (wolf->monster->data[i].temp_1);
	wolf->monster->data[i].temp_3 = wolf->player->fov - (wolf->monster->data[i].temp_2);
	wolf->monster->data[i].temp_4 = wolf->player->dir;
	wolf->monster->data[i].temp_5 = wolf->monster->data[i].angle;
	if (wolf->monster->data[i].angle < RAD_90 && wolf->player->dir > RAD_270)
	{
		if (wolf->monster->data[i].angle < wolf->player->dir)
			wolf->monster->data[i].temp_4 = wolf->player->dir - RAD_360;
		if (wolf->monster->data[i].angle > wolf->player->dir)
			wolf->monster->data[i].temp_5 = wolf->monster->data[i].angle - RAD_360;
	}
	if (wolf->player->dir < RAD_90 && wolf->monster->data[i].angle > RAD_270)
	{
		if (wolf->monster->data[i].angle < wolf->player->dir)
			wolf->monster->data[i].temp_4 = wolf->player->dir - RAD_360;
		if (wolf->monster->data[i].angle > wolf->player->dir)
			wolf->monster->data[i].temp_5 = wolf->monster->data[i].angle - RAD_360;
	}
	if (wolf->monster->data[i].temp_3 < RAD_0 && wolf->monster->data[i].temp_5 < wolf->monster->data[i].temp_4)
		wolf->monster->data[i].temp_3 = wolf->player->fov + RAD_360 - (wolf->monster->data[i].temp_2);
}

void    render_monster(t_wolf *wolf, SDL_Surface *surface)
{
	// if (!wolf->monster->data[0]->dist)
	// {
		int i = 0;
		while (i < wolf->monster->count_monster)
		{
			ft_bzero(&(wolf->monster->data[i]), sizeof(t_coin));
			if (search_angle_monster(wolf, i))
				return ;
			through_zero_monster(wolf, i);
			wall_check_monster(wolf, i);
			wolf->monster->data[i].cut_vertical_img.w = (int)((wolf->monster->data[i].flag_2 - wolf->monster->data[i].flag_1)
				* (wolf->monster->image_monster[i]->w) / ((W / 32)
				* (wolf->player->dist_to_canvas / wolf->monster->data[i].dist)));
			wolf->monster->data[i].cut_vertical_img.h = (wolf->monster->image_monster[i]->w);
			wolf->monster->data[i].cut_vertical_img.x = (int)(wolf->monster->data[i].flag_1 * (wolf->monster->image_monster[i]->w)
				/ ((W / 32) * (wolf->player->dist_to_canvas / wolf->monster->data[i].dist)));
			wolf->monster->data[i].cut_vertical_img.y = 0;
			wolf->monster->data[i].img_location.w = (wolf->monster->data[i].flag_2 - wolf->monster->data[i].flag_1);
			wolf->monster->data[i].img_location.h = (W / 32) * (wolf->player->dist_to_canvas / wolf->monster->data[i].dist);
			wolf->monster->data[i].img_location.x = wolf->monster->data[i].flag_i;
			wolf->monster->data[i].img_location.y = (H / 2) - ((W / 32)
				* (wolf->player->dist_to_canvas / wolf->monster->data[i].dist)) / 2 - wolf->player->dir_y; //сюда динамическое изменение высоты постановки прикрутить
			SDL_BlitScaled(wolf->monster->image_monster[i], &(wolf->monster->data[i].cut_vertical_img),
				surface, &(wolf->monster->data[i].img_location));
			i++;
		}
	// }
}