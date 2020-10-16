#include "../includes/wolf3d.h"

void	draw_column(t_wolf *wolf, SDL_Surface *surface, t_point point, t_distance *dist, int size, int height)
{
	int color;

	int i = 0;      
	while (point.y < size)
	{
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

void	floorcast(t_wolf *wolf, t_distance *dist, int x, int y, float dir)
{
	float curr_dist;
	float weight;
	float currFloorX;
	float currFloorY;
	int textx;
	int texty;
	int color;
	float ratio;
	float distance;
	float xend;
	float yend;

	while (y < H)
	{
		
		ratio = ((float)H / (float)(2 * y - H));
		distance = floorf((wolf->player->dist_to_canvas * ratio) / cosf(dir)); 
		xend = floorf(distance * cosf(dir)) + wolf->player->x;
		yend = floorf(distance * sinf(dir)) + wolf->player->y;
		int cellx = (int)(xend / CUBE);
		int celly = (int)(yend / CUBE);

		int tilex = (int)(yend) % CUBE;
		int tiley = (int)(xend) % CUBE;
		if (tilex < 0)
			tilex = 0;
		if (tiley < 0)
			tiley = 0;
		//printf("%d %d\n", tilex, tiley);
		color = getpixel(wolf->sdl->textures, tilex, tiley);
		set_pixel(wolf->surface, x, y, color);
		y++;
		
		/*
		curr_dist = (float)H / (float)(2 * y - H);
		weight = curr_dist / (dist->dist);
		currFloorX = weight * dist->coords.x + (1.f - weight) * wolf->player->x;
		currFloorY = weight * dist->coords.y + (1.f - weight) * wolf->player->y;
		textx = (int)(currFloorX * CUBE) % CUBE;
		texty = (int)(currFloorY * CUBE) % CUBE;
		if (textx < 0)
			textx = 0;
		if (texty < 0)
			texty = 0;
		
		set_pixel(wolf->surface, x, y, color);
		color = getpixel(wolf->sdl->textures, textx + CUBE * 5, texty);
		set_pixel(wolf->surface, x, H - y, color);
		y++;
		*/
	}
}


void	pseudo_3d(t_wolf *wolf, t_player *player, SDL_Surface *surface)
{
    t_point point;
    int     count_distance;
	float dir;
	float step;

	point.x = 0;
    point.y = 0;
	count_distance = W - 1; //номер луча с конца
	dir = player->dir;
	add_arc(&dir, player->fov / 2);
	step = player->fov / W;
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
			
			floorcast(wolf, player->distance[count_distance], point.x, H - point.y, dir);
			// draw_floor(wolf, surface, point.x, H - point.y + 1);
		}
		count_distance--; // следующий луч
		point.x++;
		add_arc(&dir, -step);
	}
}