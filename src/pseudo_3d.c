#include "../includes/wolf3d.h"

void	draw_column(t_wolf *wolf, SDL_Surface *surface, t_point point, t_distance *dist, int size, int height)
{
	int color;

	int i = 0;      
	while (point.y < size)
	{
		/*
		if (point.x == W / 2)
			printf("%d\n", height);
			*/
		if (dist->tex == 'W')
			color = getpixel(wolf->sdl->textures, dist->offsetx + CUBE * 0, i * CUBE / height);
		else if (dist->tex == 'S')
			color = getpixel(wolf->sdl->textures, dist->offsetx + CUBE * 1, i * CUBE / height);
		else if (dist->tex == 'N')
			color = getpixel(wolf->sdl->textures, dist->offsetx + CUBE * 2, i * CUBE / height);
		else if (dist->tex == 'E')
			color = getpixel(wolf->sdl->textures, dist->offsetx + CUBE * 6, i * CUBE / height);
		if (point.y > 0 && point.y < H)
			set_pixel(surface, point.x, point.y, color);
		point.y++;
		i++;
	}
}



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

void	floorcast(t_wolf *wolf, t_distance *dist, int x, int y)
{
	float curr_dist;
	float weight;
	float currFloorX;
	float currFloorY;
	int textx;
	int texty;
	int color;

	while (y < H)
	{
		curr_dist = (float)H / (float)(2 * y - H);
		weight = curr_dist / (dist->dist);
		currFloorX = weight * dist->coords.x + (1.f - weight) * wolf->player->start.x;
		currFloorY = weight * dist->coords.y + (1.f - weight) * wolf->player->start.y;
		textx = (int)(currFloorX * CUBE) % CUBE;
		texty = (int)(currFloorY * CUBE) % CUBE;
		if (textx < 0)
			textx = 0;
		if (texty < 0)
			texty = 0;
		color = getpixel(wolf->sdl->textures, textx, texty);
		set_pixel(wolf->surface, x, y, color);
		color = getpixel(wolf->sdl->textures, textx + CUBE * 5, texty);
		set_pixel(wolf->surface, x, H - y, color);
		y++;
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
		if (player->distance[count_distance]->dist != 0) // проверка сталкивается ли луч с чем либо 
		{
			point.y = ceilf((CUBE * player->dist_to_canvas) / player->distance[count_distance]->dist);
			//printf("%d\n", point.y);
			point.y = (H - point.y) / 2; // половина не закрашеной части по игрек (низ или верх) колличество пикселей
			int height = H - point.y * 2;
			//printf("%d %f\n", point.x, height);
			int temp = point.y;
			draw_column(wolf, surface, point, player->distance[count_distance], H - point.y, height);
			// draw_sky(wolf, (int)((dir / RAD_360) * wolf->sdl->sky->w),point.x, point.y);
			
			floorcast(wolf, player->distance[count_distance], point.x, H - point.y + 1);
			// draw_floor(wolf, surface, point.x, H - point.y + 1);
		}
		count_distance--; // следующий луч
		point.x++;
		add_arc(&dir, step);
	}
}