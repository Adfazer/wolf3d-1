#include "../includes/wolf3d.h"

void	draw_column(t_wolf *wolf, SDL_Surface *surface, t_point point, t_distance dist, int size, float height)
{
	int color;

	/*
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
	*/	
	int y_start = point.y;

	int i = 0;      
	while (point.y < size) // закрашиваем стенку по игреку или можно както сразу #строку# по вертикали закрсить ??
	{
		if (dist.tex == 'W')
			color = getpixel(wolf->sdl->textures, dist.offsetx, (int)(((float)i / height) * CUBE));
		else if (dist.tex == 'S')
			color = getpixel(wolf->sdl->textures, dist.offsetx + CUBE, (int)(((float)i / height) * CUBE));
		else if (dist.tex == 'N')
			color = getpixel(wolf->sdl->textures, dist.offsetx + CUBE * 2, (int)(((float)i / height) * CUBE));
		else if (dist.tex == 'E')
			color = getpixel(wolf->sdl->textures, dist.offsetx + CUBE * 3, (int)(((float)i / height) * CUBE));
		if (point.y > 0 && point.y < H)
			set_pixel(surface, point.x, point.y, color);
		point.y++;
		i++;
	}
}

# define COLOR_SKY_BLUE  0x15DAEA
# define COLOR_GREY  0xAAAAAA
# define COLOR_BROWN 0xBE8641

void	draw_floor(t_wolf *wolf, SDL_Surface *surface, int x, int y)
{
	while (y < W)
	{
		set_pixel(surface, x, y, COLOR_BROWN);
		y++;
	}	
}

void	draw_sky(t_wolf *wolf, int xtex, int x, int y)
{
	int		i;
	i = -1;
	
	while (++i < y)
	{
		set_pixel(wolf->surface, x, i, getpixel(wolf->sdl->sky, x + wolf->sdl->skybox_offset, i));
	}
}

void	floorcast(t_wolf *wolf, SDL_Surface *surface, int y)
{
	while (y < W)
	{
		
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
	float dir = player->dir;
	add_arc(&dir, -RAD_30);
	float step = RAD_60 / W;
	while (point.x < W)
	{
		if (player->distance[count_distance].dist != 0) // проверка сталкивается ли луч с чем либо 
		{
			point.y = ceilf((CUBE * player->dist_to_canvas) / player->distance[count_distance].dist);
			//printf("%d\n", point.y);
			point.y = (H - point.y) / 2; // половина не закрашеной части по игрек (низ или верх) колличество пикселей
			float height = H - point.y * 2;
			//printf("%d %f\n", point.x, height);
			draw_column(wolf, surface, point, player->distance[count_distance], H - point.y, height);
			//draw_sky(wolf, (int)((dir / RAD_360) * wolf->sdl->sky->w),point.x, point.y);
			
			//floorcast(wolf, surface, H - point.y + 1);
			//draw_floor(wolf, surface, point.x, H - point.y + 1);	
		}
		count_distance--; // следующий луч
		point.x++;
		add_arc(&dir, step);
	}
}