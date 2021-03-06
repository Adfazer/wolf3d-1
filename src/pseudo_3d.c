/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by clala             #+#    #+#             */
/*   Updated: 2020/10/24 21:56:30 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	draw_column(t_wolf *wolf,
t_point point, t_distance *dist, int size)
{
	int	color;
	int	i;
	int	height;

	i = 0;
	height = H - point.y * 2;
	while (point.y < size)
	{
		color = get_pixel(wolf->sdl->textures, dist->offsetx + \
		wolf->sdl->tex_arr[(int)dist->tex], i * CUBE / height);
		if (point.y - wolf->player->dir_y > 0 && point.y - wolf->player->dir_y < H)
			set_pixel(wolf->surface, point.x, point.y - wolf->player->dir_y, color);
		point.y++;
		i++;
	}
}

void	draw_floor(SDL_Surface *surface, int x, int y)
{
	if (y < 0)
		y = 0;
	while (y < H)
	{
		set_pixel(surface, x, y, COLOR_GREY_LIGHT);
		y++;
	}
}

void	draw_sky(t_wolf *wolf, int x, int y)
{
	int		i;
	int		to_draw;

	i = -1;
	if (y < 0)
		y = 0;
	if (y > H)
		y = H;
	while (++i < y)
	{
		to_draw = i < wolf->sdl->sky->h - 1 ? i : wolf->sdl->sky->h / 2;
		set_pixel(wolf->surface, x, i, get_pixel(wolf->sdl->sky,
			x + wolf->sdl->skybox_offset, to_draw));
	}
}

void	pseudo_3d(t_wolf *wolf, t_player *player, SDL_Surface *surface)
{
	t_point	point;
	int		count_distance;
	float	dir;

	count_distance = W - 1;
	dir = player->dir;
	add_arc(&dir, player->fov / 2);
	point.y = 0;
	if (wolf->sdl->interlaced_rendering == 0)
		point.x = 0;
	else
		point.x = 1;
	while (point.x < W)
	{
		if (player->distance[count_distance]->dist != 0)
		{
			point.y = ceilf((CUBE * player->dist_to_canvas)
				/ player->distance[count_distance]->dist);
			point.y = (H - point.y) / 2;
			draw_column(wolf, point,
				player->distance[count_distance], H - point.y);
			draw_sky(wolf, point.x, point.y - wolf->player->dir_y);
			draw_floor(surface, point.x, H - point.y - wolf->player->dir_y);
		}
		count_distance -= 2;
		point.x += 2;
		add_arc(&dir, -player->step);
	}
	if (wolf->sdl->interlaced_rendering == 0)
		wolf->sdl->interlaced_rendering = 1;
	else
		wolf->sdl->interlaced_rendering = 0;
}