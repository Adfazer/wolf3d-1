#include "wolf3d.h"

void draw_line(SDL_Surface *surface, t_point start, t_point end, int color)
{
	int dx = abs(end.x-start.x), sx = start.x<end.x ? 1 : -1;
	int dy = abs(end.y-start.y), sy = start.y<end.y ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;

	while (1)
	{
		if (start.x > W || start.x < 0 || start.y > H || start.y < 0)
			break ;
		set_pixel(surface, start.x, start.y, color);
		if (start.x==end.x && start.y==end.y)
			break;
		e2 = err;
		if (e2 >-dx)
		{
			err -= dy; start.x += sx;
		}
		if (e2 < dy)
		{
			err += dx; start.y += sy;
		}
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
			set_pixel(surface, temp.x, temp.y, color);
		}
	}
}

void draw_ray(SDL_Surface *surface, float dir, int x, int y)
{
	int dx0 = cos(dir - RAD_60 / 2) * CUBE;
	int dy0 = sin(dir - RAD_60 / 2) * CUBE;
	int dx1 = cos(dir + RAD_60 / 2) * CUBE;
	int dy1 = sin(dir + RAD_60 / 2) * CUBE;
	
	draw_line(
		surface,
		dot(x, y),
		dot(x + dx0, y - dy0),
		COLOR_WHITE);
		
	draw_line(
		surface,
		dot(x, y),
		dot(x + dx1, y - dy1),
		COLOR_WHITE);
}



void draw_background(SDL_Surface *surface)
{
	int		i;
	int		j;

	i = -1;
	while (++i < W)
	{
		j = -1;
		while (++j < H)
		{
			set_pixel(surface, i, j, COLOR_BLACK);
		}
	}
}

void	draw_minimap(SDL_Surface *surface, t_map *map, t_player *p)
{
	int	xx;
	int	yy;
	int	i;

	if (!map->mm_show)
		return ;
	draw_rectangle(surface, map->mm_start,
	dot(map->mm_w, map->mm_h), 
	COLOR_GREY_LIGHT);
	i = -1;
	while (++i < map->h * map->w)
	{
		if (ft_strchr(WALLSET, map->map[i]))
		{
			xx = (i % map->w) * map->mm_cube + map->mm_start.x;
			yy = (i / map->w) * map->mm_cube + map->mm_start.y;
			draw_rectangle(surface, dot(xx, yy),
			dot(map->mm_cube, map->mm_cube), 0xbbbb00);
		}
	}
	draw_rectangle(surface, 
		dot(p->x * map->mm_cube_coef + (map->mm_start.x - map->mm_p_size), p->y * map->mm_cube_coef + (map->mm_start.y - map->mm_p_size)),
		dot(map->mm_p_size * 2, map->mm_p_size * 2), 
		0xFFFFFF);
	draw_ray(surface, p->dir, p->x * map->mm_cube_coef + map->mm_start.x, p->y * map->mm_cube_coef + map->mm_start.y);
}
