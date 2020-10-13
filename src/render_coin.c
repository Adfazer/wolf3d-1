#include "../includes/wolf3d.h"

void	render_coin(t_wolf *wolf, SDL_Surface *surface)
{
	// из позиций игрока и коина узнать радиан направления дистанцию и если радиан направления
	// входид в угол обзора игрока перемасштабировать сурфейс коина и вывести
	//
	float	angle = 0;
	float	dist = 0;

	dist = sqrtf(powf((wolf->bon->coint_pos.x - wolf->player->x), 2) + powf((wolf->bon->coint_pos.y - wolf->player->y), 2));
	// angle_y = ((wolf->player->y - wolf->bon->coint_pos.y) / dist);
	// angle_x = ((wolf->player->x - wolf->bon->coint_pos.x) / dist);
	if (wolf->bon->coint_pos.x - wolf->player->x > 0 && wolf->bon->coint_pos.y - wolf->player->y < 0) // 2
		angle = asin((wolf->player->y - wolf->bon->coint_pos.y) / dist);
	else if (wolf->bon->coint_pos.x - wolf->player->x < 0 && wolf->bon->coint_pos.y - wolf->player->y < 0) // 1
		angle = asin((wolf->bon->coint_pos.y - wolf->player->y) / dist) + RAD_180;
	else if (wolf->bon->coint_pos.x - wolf->player->x < 0 && wolf->bon->coint_pos.y - wolf->player->y > 0) //3
		angle = asin((wolf->bon->coint_pos.y - wolf->player->y) / dist) + RAD_180;
	else if (wolf->bon->coint_pos.x - wolf->player->x > 0 && wolf->bon->coint_pos.y - wolf->player->y > 0)
		angle = asin((wolf->player->y - wolf->bon->coint_pos.y) / dist) + RAD_360;
	if (angle < wolf->player->dir + wolf->player->fov / 2 && angle > wolf->player->dir - wolf->player->fov / 2)
	{
		SDL_Rect	imgLocation;

		imgLocation.w = (W / 10) * (wolf->player->dist_to_canvas / dist);
		imgLocation.h = (H / 10) * (wolf->player->dist_to_canvas / dist);
		imgLocation.x = (W / wolf->player->fov) * (wolf->player->fov - (angle - (wolf->player->dir - wolf->player->fov / 2))) - ((W / 10) * (wolf->player->dist_to_canvas / dist)) / 2;
		imgLocation.y = (H / 2) - ((H / 10) * (wolf->player->dist_to_canvas / dist)) / 2;

		SDL_BlitScaled(wolf->bon->image_coin, NULL, surface, &imgLocation);

	}

	// printf("%f\n", angle * 180 / 3.141592);;
	// printf("%f\n", angle_y * 180 / 3.141592);
	// printf("%f\n", angle_x * 180 / 3.141592);
}