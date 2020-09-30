#include "wolf3d.h"

static int	x_to_mm(int x)
{
	return map.mm_start.x + x / (map.mm.x);
}

static int	y_to_mm(int y)
{
	return map.mm_start.y + y / (map.mm.y);
}

void draw_line(SDL_Surface *surface, t_point start, t_point end, int color)
{
	
		int dx = abs(end.x-start.x), sx = start.x<end.x ? 1 : -1;
		int dy = abs(end.y-start.y), sy = start.y<end.y ? 1 : -1; 
		int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;)
	{
		if (start.x > W || start.x < 0 || start.y > H || start.y < 0)
			break ;
		set_pixel(surface, start, color);
		if (start.x==end.x && start.y==end.y)
			break;
		e2 = err;
		if (e2 >-dx) { err -= dy; start.x += sx; }
		if (e2 < dy) { err += dx; start.y += sy; }
	}
}

void	draw_rectangle(SDL_Surface *surface, t_point start, t_point width_height,int color)
{
	int	i;
	int j;
	t_point	temp;

	i = -1;
	while (++i < width_height.y)
	{
		j = -1;
		temp.y = i + start.y;
		while (++j < width_height.x)
		{
			temp.x = j + start.x;
			set_pixel(surface, temp, color);
		}
	}
}

void drawRay(SDL_Surface *surface, int x, int y)
{
	int dx0 = cos(p.dir) * CUBE;
	int dy0 = sin(p.dir) * CUBE;
	draw_line(
		surface,
		dot(x, y),
		dot(x + dx0, y - dy0),
		color_to_hex(255, 255, 255));
	/*
	int dx0 = cos(p.dir - RAD_60 / 2) * CUBE;
	int dy0 = sin(p.dir - RAD_60 / 2) * CUBE;
	int dx1 = cos(p.dir + RAD_60 / 2) * CUBE;
	int dy1 = sin(p.dir + RAD_60 / 2) * CUBE;
	
	draw_line(
		surface,
		dot(x, y),
		dot(x + dx0, y - dy0),
		color_to_hex(255, 255, 255));
		
	draw_line(
		surface,
		dot(x, y),
		dot(x + dx1, y - dy1),
		color_to_hex(255, 255, 255));
		*/
}

void draw_background(SDL_Surface *surface)
{
	draw_rectangle(surface, dot(0,0), dot(W, H), 0);
}

void draw_minimap(SDL_Surface *surface)
{
	map.minimap_width = 5;
	int p_size = 20;
	
	draw_rectangle(surface, map.mm_start,
	dot(map.mm_cube.x * map.w, map.mm_cube.y * map.h), 
	color_to_hex(121,121,121));

	for (int i = 0; i < map.h * map.w; i++)
	{
		if (map.map[i] == TEX_BORDER)
		{
			int xx = x_to_mm((i % map.w ) * CUBE);
			int yy = y_to_mm((i / map.h) * CUBE);
			draw_rectangle(surface, \
			dot(xx, yy),
			dot(CUBE / (map.mm.x), CUBE / (map.mm.y)), 0xbbbb00);
		}
	}

	draw_rectangle(surface, 
		dot(p.x / map.mm.x + map.mm_start.x - PLAYER_MM_SIZE, p.y / map.mm.y + map.mm_start.y - PLAYER_MM_SIZE),
		dot(p_size / map.mm.x + PLAYER_MM_SIZE, p_size / map.mm.y + PLAYER_MM_SIZE), 
		color_to_hex(255,255,255));
	drawRay(surface, p.x / map.mm.x + map.mm_start.x, p.y / map.mm.y + map.mm_start.y);
}
