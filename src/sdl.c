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
	if (is_texture(map, p->x + dx + player_box, p->y, TEX_FLOOR) || is_texture(map, p->x + dx + player_box, p->y, TEX_COIN))
	{
		p->x += dx;
	}
	player_box = dy > 0 ? p->size : -p->size;
	if (is_texture(map, p->x, p->y + dy + player_box, TEX_FLOOR) || is_texture(map, p->x, p->y + dy + player_box, TEX_COIN))
	{
		p->y += dy;
	}
}

void handle_keys(t_wolf *wolf, SDL_Event event, t_map *map, t_player *p)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			wolf->sdl->run = false;
		if (event.key.keysym.sym == SDLK_d)
			calc_move(wolf->map, p, p->speed * sinf(p->dir + RAD_90), -(p->speed * cosf(p->dir + RAD_90)));
		if (event.key.keysym.sym == SDLK_a)
			calc_move(map, p, p->speed * sinf(p->dir - RAD_90), -(p->speed * cosf(p->dir - RAD_90)));
		if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
			calc_move(map, p, p->speed * sinf(p->dir), -(p->speed * cosf(p->dir)));
		if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
			calc_move(map, p, -(p->speed * sinf(p->dir)), p->speed * cosf(p->dir));
		if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
		{
			if (event.key.keysym.sym == SDLK_RIGHT)
			{
				add_arc(&p->dir, -RAD_30);
				add_skybox_offset(wolf->sdl, 52);
			}
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				add_arc(&p->dir, RAD_30);
				add_skybox_offset(wolf->sdl, -52);
			}
		}
		if (event.key.keysym.sym == SDLK_p)
			wolf->sdl->sides_mode = wolf->sdl->sides_mode == 1 ? 0 : 1;
		if (event.key.keysym.sym == SDLK_m)
			map->mm_show = map->mm_show == 1 ? 0 : 1;
		if (event.key.keysym.sym == SDLK_o)
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
		if (event.key.keysym.sym == SDLK_i)
		{
			if (wolf->bon->fps == 0)
				wolf->bon->fps = 1;
			else
				wolf->bon->fps = 0;
		}
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			wolf->bon->guns_fire = 1;
		}
	}
}

void sdl_init(t_wolf *wolf, t_map *map, t_player *p)
{
	SDL_Window* window = NULL;
    window = SDL_CreateWindow("Wolf3d", 100, 
                                100, W, H, 
                                SDL_WINDOW_SHOWN);

	SDL_Surface* icon;
	if (!(icon = SDL_LoadBMP(ICON_PATH)))
		printf("%s\n", SDL_GetError());
	if (!(wolf->sdl->sky = SDL_LoadBMP(SKY_PATH)))
		printf("%s\n", SDL_GetError());	
	SDL_SetWindowIcon(window, icon);
    if (!window)
        printf("window error\n");
    
	wolf->sdl->sides_mode = 1;

    SDL_Surface *surface;
    surface = SDL_GetWindowSurface(window);
	wolf->sdl->skybox_offset = 0;
	wolf->surface = surface;
        SDL_UpdateWindowSurface(window);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_Event event;
		int x = -0x7ffff;
		wolf->sdl->run = 1;
		while (wolf->sdl->run)
		{
			if (SDL_PollEvent( & event))
			{
				if (event.type == SDL_QUIT)
					wolf->sdl->run = false;
				if (event.type == SDL_MOUSEMOTION)
				{
					rotate(wolf, &event, &x);
					//debug_player(player);
				}
				// if( event.type == SDL_MOUSEBUTTONDOWN )
				// {
        		// 	if( event.button.button == SDL_BUTTON_LEFT )
				// 		p->guns_fire = 1;
				// }
				// if( event.type == SDL_MOUSEBUTTONUP )
				// {
        		// 	if( event.button.button == SDL_BUTTON_LEFT )
				// 		p->guns_fire = 0;
				// }
				handle_keys(wolf, event, wolf->map, wolf->player);
			}
			draw_background(surface);
			all_get_distance(wolf);
			pseudo_3d(wolf, p, surface);
			render_coin(wolf, surface);
        	render_fps(surface, wolf->bon);
			render_shot(wolf, surface);
			draw_minimap(wolf, surface, map, p);
			SDL_UpdateWindowSurface(window);
		}
        SDL_DestroyWindow(window);
		TTF_Quit();
        SDL_Quit();
}
