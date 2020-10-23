/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 18:31:46 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	draw_column(t_wolf *wolf, SDL_Surface *surface, t_point point, t_distance *dist, int size, int height)
{
	int color;

	int i = 0;      
	while (point.y < size)
	{
		color = get_pixel(wolf->sdl->textures, dist->offsetx + \
		wolf->sdl->tex_arr[(int)dist->tex], i * CUBE / height);
		if (point.y > 0 && point.y < H)
			set_pixel(surface, point.x, point.y, color);
		point.y++;
		i++;
	}
}

void	draw_floor(SDL_Surface *surface, int x, int y)
{
	while (y < H)
	{
		set_pixel(surface, x, y, COLOR_GREY_LIGHT);
		y++;
	}	
}

void	draw_sky(t_wolf *wolf, int x, int y)
{
	int		i;
	i = -1;
	
	while (++i < y)
	{
		set_pixel(wolf->surface, x, i, get_pixel(wolf->sdl->sky, x + wolf->sdl->skybox_offset, i));
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
	count_distance = W - 1;
	dir = player->dir;
	add_arc(&dir, player->fov / 2);
	step = player->fov / W;
	while (point.x < W)
	{
		if (player->distance[count_distance]->dist != 0)
		{
			point.y = ceilf((CUBE * player->dist_to_canvas) / player->distance[count_distance]->dist);
			point.y = (H - point.y) / 2;
			int height = H - point.y * 2;
			player->distance[count_distance]->y = H - point.y;
			draw_column(wolf, surface, point, player->distance[count_distance], H - point.y, height);
			draw_sky(wolf,point.x, point.y);
			draw_floor(surface, point.x, H - point.y);
		}
		count_distance--;
		point.x++;
		add_arc(&dir, -step);
	}
}
