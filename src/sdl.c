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
	//debug_player(&p);
}


//работает, пускает в углы
void	calc_move(t_map *map, t_player *p, float dy, float dx)
{
	int		player_box;

	player_box = dx > 0 ? p->size : -p->size;
	if (is_texture(map, p->x + dx + player_box, p->y, TEX_FLOOR))
	{
		p->x += dx;
	}
	player_box = dy > 0 ? p->size : -p->size;
	if (is_texture(map, p->x, p->y + dy + player_box, TEX_FLOOR))
	{
		p->y += dy;
	}
}


void init_sdl(t_wolf *wolf, t_map *map, t_player *p)
{
	SDL_Window* window = NULL;
    window = SDL_CreateWindow("Hello, SDL 2!", 100, 
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
    
	

	Uint32 startTime = 0;
    Uint32 endTime = 0;
    Uint32 delta = 0;
    short fps = 60;
    short timePerFrame = 16; // miliseconds
	
	int flag_guns = 0;
	Uint32 start_guns;


    SDL_Surface *surface;
    surface = SDL_GetWindowSurface(window);
	wolf->sdl->skybox_offset = 0;
	wolf->surface = surface;
	draw_minimap(surface, map, p);
	//set_pixel(surface, dot(0,0), 0xff0000);
	//wolf->sdl->bytes = (unsigned char *)wolf->surface->pixels;
	//printf("%c\n", wolf->sdl->bytes[0]);
        SDL_UpdateWindowSurface(window);
		SDL_SetRelativeMouseMode(SDL_TRUE);
        bool isquit = false;
		SDL_Event event;
		int x = -0x7ffff;
		while (!isquit)
		{
			if (SDL_PollEvent( & event))
			{
				if (event.type == SDL_QUIT)
					isquit = true;
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
				if (event.type == SDL_KEYDOWN)
				{
					isquit = event.key.keysym.sym == SDLK_ESCAPE ? true : isquit;
					
					if (event.key.keysym.sym == SDLK_d)
					{
						calc_move(map, p, p->speed * sinf(p->dir + RAD_90), -(p->speed * cosf(p->dir + RAD_90)));
						//p->y += p->speed * sinf(p->dir + RAD_90);
						//p->x -= p->speed * cosf(p->dir + RAD_90);
						// p->x = p->x > CUBE * map->w - 1? CUBE * map->w - 1 : p->x;
						//debug_player(player);
					}
					if (event.key.keysym.sym == SDLK_a)
					{
						calc_move(map, p, p->speed * sinf(p->dir - RAD_90), -(p->speed * cosf(p->dir - RAD_90)));
						//p->y += p->speed * sinf(p->dir - RAD_90);
						//p->x -= p->speed * cosf(p->dir - RAD_90);
						// p->x = p->x < 0 ? 0 : p->x;
						//debug_player(player);
					}
					if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
					{
						calc_move(map, p, p->speed * sinf(p->dir), -(p->speed * cosf(p->dir)));
						//p->y += p->speed * sinf(p->dir);
						//p->x -= p->speed * cosf(p->dir);
						// p->y = p->y > CUBE * map->h - 1 ? CUBE * map->h - 1 : p->y;
					}
					if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
					{
						calc_move(map, p, -(p->speed * sinf(p->dir)), p->speed * cosf(p->dir));
						//p->y -= p->speed * sinf(p->dir);
						//p->x += p->speed * cosf(p->dir);
						// p->y = p->y < 0 ? 0 : p->y;
					}
					if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
					{
						if (event.key.keysym.sym == SDLK_RIGHT)
						{
							add_arc(&p->dir, -RAD_1);
							add_skybox_offset(wolf->sdl, 2);
						}
						if (event.key.keysym.sym == SDLK_LEFT)
						{
							add_arc(&p->dir, RAD_1);
							add_skybox_offset(wolf->sdl, -2);
						}
					}
					if (event.key.keysym.sym == SDLK_p)
						p->sides = p->sides == 1 ? 0 : 1;
					if (event.key.keysym.sym == SDLK_m)
						map->mm_show = map->mm_show == 1 ? 0 : 1;
					if (event.key.keysym.sym == SDLK_o)
					{
						if (p->music_flag == 0)
						{
							Mix_PlayMusic(p->music, -1);
							p->music_flag = 1;
						}
						else
						{
							p->music_flag = 0;
							Mix_HaltMusic();
						}
					}
					if (event.key.keysym.sym == SDLK_i)
					{
						if (p->fps == 0)
							p->fps = 1;
						else
							p->fps = 0;
					}
					if (event.key.keysym.sym == SDLK_SPACE)
					{
						p->guns_fire = 1;
					}
				}
    		}
			// music(p);

			if (!startTime) {
            // get the time in ms passed from the moment the program started
            startTime = SDL_GetTicks(); 
			} else {
				delta = endTime - startTime; // how many ms for a frame
			}
			// if less than 16ms, delay 
			if (delta < timePerFrame) {
				SDL_Delay(timePerFrame - delta);
			}
			// if delta is bigger than 16ms between frames, get the actual fps
			if (delta > timePerFrame) {
				fps = 1000 / delta;
			}
     	   	startTime = endTime;
       		endTime = SDL_GetTicks();
			
			//draw_background(surface);
			all_get_distance(map, p);
			pseudo_3d(wolf, p, surface);
			if (p->fps)
        		render_fps(fps, surface);
			if (p->guns_fire || flag_guns != 0)
			{
				p->guns_fire = 0;
				if (!start_guns)
				{
					flag_guns++;
					start_guns = SDL_GetTicks();
				}
				if (start_guns + 200 < SDL_GetTicks())
				{
					flag_guns++;
					start_guns = SDL_GetTicks();
				}
				guns_shot(surface, flag_guns);
				flag_guns == 5 ? Mix_HaltMusic(): 0;
				flag_guns == 5 ? flag_guns = 0: 0;
			}
			else
				guns_shot(surface, 1);
			draw_minimap(surface, map, p);
			/*
			for (int o = 0; o < CUBE; o++)
			{
				for (int p = 0; p < CUBE; p++)
				{
					set_pixel(surface, dot(p,o), getpixel(wolf->sdl->textures, p, o));
				}
			}
			*/
		//debug_player(p);
			SDL_UpdateWindowSurface(window);
		}
        SDL_DestroyWindow(window);
		TTF_Quit();
        SDL_Quit();
}
