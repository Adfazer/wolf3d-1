#include "wolf3d.h"


static void rotate(SDL_Event *event, int *x, t_player *p)
{
	if (event->motion.xrel >= 0)
		add_arc(&(p->dir), -0.02);
	else
		add_arc(&(p->dir), 0.02);
	*x = event->motion.x;
	//debug_player(&p);
}


//работает, пускает в углы
void	calc_move(t_map *map, t_player *p, float dy, float dx)
{
	if (is_texture(map, p->x + dx, p->y, TEX_FLOOR))
		p->x += dx;
	if (is_texture(map, p->x, p->y + dy, TEX_FLOOR))
		p->y += dy;
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
	SDL_SetWindowIcon(window, icon);
    if (!window)
        printf("window error\n");
    
	

	Uint32 startTime = 0;
    Uint32 endTime = 0;
    Uint32 delta = 0;
    short fps = 60;
    short timePerFrame = 16; // miliseconds

    SDL_Surface *surface = wolf->surface;
    surface = SDL_GetWindowSurface(window);
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
					rotate(&event, &x, p);
					//debug_player(player);
				}
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
							add_arc(&p->dir, -RAD_1);
						if (event.key.keysym.sym == SDLK_LEFT)
							add_arc(&p->dir, RAD_1);
					}
					if (event.key.keysym.sym == SDLK_p)
						p->sides = p->sides == 1 ? 0 : 1;
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
				}
    		}
			// music(p);
			draw_background(surface);
			all_get_distance(map, p);
			pseudo_3d(wolf, p, surface);
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
			SDL_UpdateWindowSurface(window);
			
			
			
			
		}
		
        SDL_DestroyWindow(window);
        SDL_Quit();
}
