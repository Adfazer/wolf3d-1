#include "../includes/wolf3d.h"

void	draw_column(t_wolf *wolf, SDL_Surface *surface, t_point point, t_distance dist, int size, int offsety)
{
	int color;

	color = dist.tex == '*' ? 0x0000ff : 0x00ff00;
	if (dist.tex == '*')
		color = 0x0000ff;
	else if (dist.tex == '#')
		color = 0x00ff00;
	else if (dist.tex == 'S')
		color = 0x231232;
	else if (dist.tex == 'N')
		color = 0x550132;
	else if (dist.tex == 'E')
		color = 0xffffff;
	else if (dist.tex == 'W')
		color = 0x111111;
	int y_start = point.y;
	float height = size - point.y;
	//printf("%d\n", point.y);
	int i = 0;
	       
	while (point.y < size) // закрашиваем стенку по игреку или можно както сразу #строку# по вертикали закрсить ??
	{
		int y = point.y + W / 2 - size / 2;
		if (dist.tex == 'W')
			color = getpixel(wolf->sdl->textures, dist.offsetx, (int)(((float)i / height) * (CUBE - 2 * offsety)) + offsety);
		else if (dist.tex == 'S')
			color = getpixel(wolf->sdl->textures, dist.offsetx + CUBE, (int)(((float)i / height) * (CUBE - 2 * offsety)) + offsety);
		else if (dist.tex == 'N')
			color = getpixel(wolf->sdl->textures, dist.offsetx + CUBE * 2, (int)(((float)i / height) * (CUBE - 2 * offsety)) + offsety);
		else if (dist.tex == 'E')
			color = getpixel(wolf->sdl->textures, dist.offsetx + CUBE * 3, (int)(((float)i / height) * (CUBE - 2 * offsety)) + offsety);
		set_pixel(surface, point, color);
		point.y++;
		i++;
	}
}

void	pseudo_3d(t_wolf *wolf, t_player *player, SDL_Surface *surface)
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
		if (player->distance[count_distance].dist != 0) // проверка сталкивается ли луч с чем либо 
		{
			// y = (int)((1 - (data->player.distance[count_distance] / data->player.visibility)) * data->h);
			point.y =  (CUBE * player->dist_to_canvas) /  player->distance[count_distance].dist;
			// point.y = (int)(((2.0f * atan((1.0f / (2.0f * (float)player->distance[count_distance])))) / ((float)H / ((float)W / (float)(player->fov * 0.02)))) * (float)H);
			
			//что то альфа = 2 * арктан(1/2*дистанция)] находим колличество пикселей по игрек от серидины в обе стороны которые надо закрасить 
			if (point.y > H) // затычка чтоб не крашилось при залете в стенку 
				point.y = H;
			int cash = H;
			cash = (cash - point.y) / 2; // половина не закрашеной части по игрек (низ или верх) колличество пикселей
			point.y = cash;
			int y1 = point.y;
			int offsety = 0;

			
			if (player->distance[count_distance].dist < player->dist_to_canvas)
			{
				offsety = (int)(CUBE / player->dist_to_canvas) * player->distance[count_distance].dist;
				//printf("%d\n", offsety);
			}
			
			
			draw_column(wolf, surface, point, player->distance[count_distance], H - y1, offsety);
			
			//draw_column();
			
			//ft_printf("%d %d %d\n", point.y, y1, count_distance);
			
		}
		count_distance--; // следующий луч
		point.x++;;
	}
}

// void set_pixel(SDL_Surface *surface, t_point point, Uint32 pixel)
// {
//   Uint32 *target_pixel = (Uint32 *)((Uint8 *)surface->pixels + point.y * surface->pitch
//   	 + point.x * sizeof *target_pixel);
//  	 *target_pixel = pixel;
// }