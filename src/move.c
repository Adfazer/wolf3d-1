/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:32:04 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 19:44:38 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	add_skybox_offset(t_sdl *sdl, int to_add)
{
	sdl->skybox_offset += to_add;
	if (sdl->skybox_offset > sdl->sky->w - 1)
		sdl->skybox_offset -= sdl->sky->w;
	if (sdl->skybox_offset < 0)
		sdl->skybox_offset += sdl->sky->w;
}

void	rotate(t_wolf *wolf, SDL_Event *event, int *x)
{
	if (event->motion.xrel >= 0)
	{
		add_arc(&(wolf->player->dir), -0.02);
		add_skybox_offset(wolf->sdl, 2);
	}
	else
	{
		add_arc(&(wolf->player->dir), 0.02);
		add_skybox_offset(wolf->sdl, -2);
	}
	*x = event->motion.x;
}

void	calc_move(t_map *map, t_player *p, float dy, float dx)
{
	int		player_box;

	player_box = dx > 0 ? p->size : -p->size;
	if (is_texture(map, p->x + dx + player_box, p->y, TEX_FLOOR)
	|| is_texture(map, p->x + dx + player_box, p->y, TEX_COIN))
	{
		p->x += dx;
	}
	player_box = dy > 0 ? p->size : -p->size;
	if (is_texture(map, p->x, p->y + dy + player_box, TEX_FLOOR) ||
	is_texture(map, p->x, p->y + dy + player_box, TEX_COIN))
	{
		p->y += dy;
	}
}
