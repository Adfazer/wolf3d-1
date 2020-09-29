#include "../includes/wolf3d.h"

void	pseudo_3d(t_player *player)
{
    t_point point;
    int     count_distance;

    point.x = 0;
    point.y = 0;
	count_distance = W - 1; //номер луча с конца
	int color = 255;
	// data->color = mlx_get_color_value(data->mlx_p, 6560200);
    // ft_printf("%f--mydis\n", player->distance[W / 2]);
	while (point.x < W)
	{
		if (player->distance[count_distance] != 0) // проверка сталкивается ли луч с чем либо 
		{
			// y = (int)((1 - (data->player.distance[count_distance] / data->player.visibility)) * data->h);
			point.y = (int)(((2.0f * atan((1.0f / (2.0f * (float)player->distance[count_distance])))) / ((float)H / ((float)W / (float)(player->fov * 0.02)))) * (float)H);
			//что то альфа = 2 * арктан(1/2*дистанция)] находим колличество пикселей по игрек от серидины в обе стороны которые надо закрасить 
			if (point.y > H) // затычка чтоб не крашилось при залете в стенку 
				point.y = H;
			int cash = H;
			cash = (cash - point.y) / 2; // половина не закрашеной части по игрек (низ или верх) колличество пикселей
			point.y = cash;
			int y1 = point.y;
			while (point.y < H - y1) // закрашиваем стенку по игреку или можно както сразу #строку# по вертикали закрсить ??
			{
				set_pixel(surface, point, color);
				point.y++;
			}
		}
		count_distance--; // следующий луч
		point.x++;;
	}
}

// void set_pixel(SDL_Surface *surface, t_point point, Uint32 pixel)
// {
//   Uint32 *target_pixel = (Uint32 *)((Uint8 *)surface->pixels + point.y * surface->pitch
//   	 + point.x * sizeof *target_pixel);
//   *target_pixel = pixel;
// }