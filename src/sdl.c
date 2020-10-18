/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:32:04 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 18:48:50 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	add_skybox_offset(t_sdl *sdl, int to_add)
{
	sdl->skybox_offset += to_add;
	if (sdl->skybox_offset > sdl->sky->w - 1)
		sdl->skybox_offset -= sdl->sky->w;
	if (sdl->skybox_offset < 0)
		sdl->skybox_offset += sdl->sky->w;
}

static void rotate(t_wolf *wolf, SDL_Event *event, int *x)
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

void handle_keys(t_wolf *wolf, SDL_Event *event, t_map *map, t_player *p)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
		wolf->sdl->run = false;
	if (wolf->sdl->state[SDL_SCANCODE_D])
		calc_move(wolf->map, p, p->speed * sinf(p->dir + RAD_90), -(p->speed * cosf(p->dir + RAD_90)));
	if (wolf->sdl->state[SDL_SCANCODE_A])
		calc_move(map, p, p->speed * sinf(p->dir - RAD_90), -(p->speed * cosf(p->dir - RAD_90)));
	if (wolf->sdl->state[SDL_SCANCODE_DOWN] || wolf->sdl->state[SDL_SCANCODE_S])
		calc_move(map, p, p->speed * sinf(p->dir), -(p->speed * cosf(p->dir)));	
	if (wolf->sdl->state[SDL_SCANCODE_W] || wolf->sdl->state[SDL_SCANCODE_UP])
		calc_move(map, p, -(p->speed * sinf(p->dir)), p->speed * cosf(p->dir));
	if (wolf->sdl->state[SDL_SCANCODE_RIGHT] && add_arc(&p->dir, -RAD_30))
		add_skybox_offset(wolf->sdl, 52);
	if (wolf->sdl->state[SDL_SCANCODE_LEFT] && add_arc(&p->dir, RAD_30))
		add_skybox_offset(wolf->sdl, -52);
	if (wolf->sdl->state[SDL_SCANCODE_P])
		wolf->sdl->sides_mode = wolf->sdl->sides_mode == 1 ? 0 : 1;
	if (wolf->sdl->state[SDL_SCANCODE_M])
		map->mm_show = map->mm_show == 1 ? 0 : 1;
	if (wolf->sdl->state[SDL_SCANCODE_I])
		wolf->bon->fps = wolf->bon->fps == 0 ? 1 : 0;
	if (wolf->sdl->state[SDL_SCANCODE_SPACE])
		wolf->bon->guns_fire = 1;
	if (wolf->sdl->state[SDL_SCANCODE_O])
	{
		if (wolf->bon->music_flag == 0)
		{
			Mix_PlayMusic(wolf->bon->music, -1);
			wolf->bon->music_flag = 1;
		}
		else
		{
			wolf->bon->music_flag = 0;
			Mix_HaltMusic();
		}
	}
}

void	handle_event(t_wolf *wolf, SDL_Event *event, int *x)
{
	if (SDL_PollEvent(event))
	{
		if (event->type == SDL_QUIT)
			wolf->sdl->run = false;
		if (event->type == SDL_MOUSEMOTION)
			rotate(wolf, event, x);
		if (event->type == SDL_MOUSEBUTTONDOWN)
		{
			if(event->button.button == SDL_BUTTON_LEFT)
				wolf->bon->guns_fire = 1;
		}
		if (event->type == SDL_MOUSEBUTTONUP)
		{
			if( event->button.button == SDL_BUTTON_LEFT )
				wolf->bon->guns_fire = 0;
		}
		if (event->type == SDL_KEYDOWN)
			handle_keys(wolf, event, wolf->map, wolf->player);
	}
}

void init_sdl(t_wolf *wolf)
{
	wolf->sdl->win = SDL_CreateWindow("Wolf3d", 100,
        100, W, H, SDL_WINDOW_SHOWN);
	!wolf->sdl->win ? error(wolf, SDL_GetError()) : 0;
	if (!(wolf->sdl->icon = SDL_LoadBMP(ICON_PATH)))
		error(wolf, SDL_GetError());
	if (!(wolf->sdl->sky = SDL_LoadBMP(SKY_PATH)))
		error(wolf, SDL_GetError());
	if (!(wolf->sdl->textures = SDL_LoadBMP(TEXTURE_PATH)))
		error(wolf, SDL_GetError());
	SDL_SetWindowIcon(wolf->sdl->win, wolf->sdl->icon);
	wolf->sdl->sides_mode = 1;
    wolf->surface = SDL_GetWindowSurface(wolf->sdl->win);
	wolf->sdl->skybox_offset = 0;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	wolf->sdl->run = 1;
	wolf->sdl->state = SDL_GetKeyboardState(NULL);
}

void wolf_loop(t_wolf *wolf)
{	
	SDL_Event event;
	int x;
	
	init_sdl(wolf);
	x = -0x7fffff;
	while (wolf->sdl->run)
	{
		handle_event(wolf, &event, &x);	
		draw_background(wolf->surface);
		all_get_distance(wolf);
		pseudo_3d(wolf, wolf->player, wolf->surface);
		render_coin(wolf, wolf->surface);
		render_score_coin(wolf);
		render_fps(wolf, wolf->bon);
		render_shot(wolf, wolf->surface);
		draw_minimap(wolf, wolf->map, wolf->player);
		SDL_UpdateWindowSurface(wolf->sdl->win);
		// printf("%f %f\n", wolf->player->x, wolf->player->y);
	}
	SDL_DestroyWindow(wolf->sdl->win);
	TTF_Quit();
	SDL_Quit();
	exit(0);
}
