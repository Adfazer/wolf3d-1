#include "wolf3d.h"

void drawRay(SDL_Surface *surface, int x, int y)
{

	int dx = cos(arcToRad(p.dir)) * CUBE;
	int dy = sin(arcToRad(p.dir)) * CUBE;
	draw_line(
		surface,
		dot(x, y),
		dot(x + dx, y + dy),
		color_to_hex(255, 255, 255));
}

void drawBackground(SDL_Surface *surface)
{
	draw_rectangle(surface, dot(0,0), dot(W, H), 0);
}

void drawOverheadMap(SDL_Surface *surface)
{
	map.minimap_width = 5;
	//t_point temp;
	//int color;
	int p_size = 20;
	drawBackground(surface);

	//minimap
	draw_rectangle(surface, map.mm_start,
	dot(CUBE * map.w / map.mm.x, CUBE * map.h / map.mm.y), 
	color_to_hex(121,121,121));
	
	//player square
	draw_rectangle(surface, 
		dot(p.x / map.mm.x + map.mm_start.x - PLAYER_MM_SIZE, p.y / map.mm.y + map.mm_start.y - PLAYER_MM_SIZE),
		dot(p_size / map.mm.x + PLAYER_MM_SIZE, p_size / map.mm.y + PLAYER_MM_SIZE), 
		color_to_hex(255,255,255));
}


void set_pixel(SDL_Surface *surface, t_point point, Uint32 pixel)
{
  Uint32 *target_pixel = (Uint32 *)((Uint8 *)surface->pixels + point.y * surface->pitch
  	 + point.x * sizeof *target_pixel);
  *target_pixel = pixel;
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




static void rotate(SDL_Event *event, int *x)
{
	if (event->motion.xrel > 0)
		add_arc(&p.dir, 2);
	else
		add_arc(&p.dir, -2);
	*x = event->motion.x;
	debug_player(&p);
}

void init_sdl(t_map *map, t_player *player)
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
        printf("error\n");
        exit(1);
    }    
    SDL_Window* window = NULL;
    window = SDL_CreateWindow("Hello, SDL 2!", 100, 
                                100, W, H, 
                                SDL_WINDOW_SHOWN);
    if (!window)
        printf("window error\n");
    
    surface = NULL;
    
    surface = SDL_GetWindowSurface(window);
    
        //SDL_FillRect(surface, NULL, SDL_MapRGB( surface->format, 0, 150, 0));
		
		//t_point s = dot(100,234);
		//t_point e = dot(400,154);;
		

		//draw_line(surface, s, e, color_to_hex(255, 0, 0));
		//draw_rectangle(surface, s, e, color_to_hex(44,44,44));
		//draw_rectangle(surface, e, s, color_to_hex(44,44,44));
        //raycast();
		drawOverheadMap(surface);
        SDL_UpdateWindowSurface(window);
		SDL_SetRelativeMouseMode(SDL_TRUE);
        //SDL_Delay(5000);
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
					rotate(&event, &x);
					debug_player(player);
				}
				if (event.type == SDL_KEYDOWN)
				{
					isquit = event.key.keysym.sym == SDLK_ESCAPE ? true : isquit;
					if (event.key.keysym.sym == SDLK_d)
					{
						p.x += CUBE;
						p.x = p.x > CUBE * map->w - 1? CUBE * map->w - 1 : p.x;
					}
					if (event.key.keysym.sym == SDLK_a)
					{
						p.x -= CUBE;
						p.x = p.x < 0 ? 0 : p.x;
					}
					if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
					{
						p.y += CUBE;
						p.y = p.y > CUBE * map->h - 1 ? CUBE * map->h - 1 : p.y;
						debug_map(map);
						debug_player(player);
					}
					if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
					{
						p.y -= CUBE;
						p.y = p.y < 0 ? 0 : p.y;
					}
					if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
					{
						if (event.key.keysym.sym == SDLK_RIGHT)
							add_arc(&p.dir, 10);
						if (event.key.keysym.sym == SDLK_LEFT)
							add_arc(&p.dir, -10);
					}

				}
    		}
			drawOverheadMap(surface);
			drawRay(surface, p.x / map->mm.x + map->mm_start.x, p.y / map->mm.y + map->mm_start.y);
			SDL_UpdateWindowSurface(window);
		}
        SDL_DestroyWindow(window);
        SDL_Quit();
}

