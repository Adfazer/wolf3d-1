#include "../includes/wolf3d.h"

void	draw_column(t_wolf *wolf, SDL_Surface *surface, t_point point, t_distance dist, int size, float height)
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

	int i = 0;      
	while (point.y < size) // закрашиваем стенку по игреку или можно както сразу #строку# по вертикали закрсить ??
	{
		if (dist.tex == 'W')
			color = getpixel(wolf->sdl->textures, dist.offsetx, (int)(((float)i / height) * 62));
		else if (dist.tex == 'S')
			color = getpixel(wolf->sdl->textures, dist.offsetx + CUBE, (int)(((float)i / height) * 62));
		else if (dist.tex == 'N')
			color = getpixel(wolf->sdl->textures, dist.offsetx + CUBE * 2, (int)(((float)i / height) * 62));
		else if (dist.tex == 'E')
			color = getpixel(wolf->sdl->textures, dist.offsetx + CUBE * 3, (int)(((float)i / height) * 62));
		if (point.y > 0 && point.y < H)
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
	while (point.x < W)
	{
		if (player->distance[count_distance].dist != 0) // проверка сталкивается ли луч с чем либо 
		{
			point.y = (CUBE * player->dist_to_canvas) /  player->distance[count_distance].dist;
			point.y = (H - point.y) / 2; // половина не закрашеной части по игрек (низ или верх) колличество пикселей
			float height = H - point.y * 2;
			draw_column(wolf, surface, point, player->distance[count_distance], H - point.y, height);			
		}
		count_distance--; // следующий луч
		point.x++;;
	}
}