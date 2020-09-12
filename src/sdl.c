#include "wolf3d.h"


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


int		color_to_hex(int r, int g, int b)
{	
	return (r << 16) | (g << 8) | b;
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
        //SDL_Delay(5000);
        bool isquit = false;
		SDL_Event event;
		while (!isquit)
		{
			if (SDL_PollEvent( & event))
			{
				if (event.type == SDL_QUIT)
					isquit = true;
				if (event.type == SDL_KEYDOWN)
				{
					isquit = event.key.keysym.sym == SDLK_ESCAPE ? true : isquit;
					if (event.key.keysym.sym == SDLK_RIGHT)
					{
						p.x += CUBE;
						p.x = p.x > CUBE * map->w * 2 - p.size ? CUBE * map->w * 2 - p.size: p.x;

					}
					if (event.key.keysym.sym == SDLK_LEFT)
					{
						p.x -= CUBE;
						p.x = p.x < 0 ? 0 : p.x;
					}
					if (event.key.keysym.sym == SDLK_DOWN)
					{
						p.y += CUBE;
						p.y = p.y > CUBE * map->h * 2 - CUBE	 - p.size ? CUBE * map->h * 2 - CUBE - p.size: p.y;
						debug_map(map);
						debug_player(player);
					}
					if (event.key.keysym.sym == SDLK_UP)
					{
						p.y -= CUBE;
						p.y = p.y < 0 ? 0 : p.y;
					}

				}
    		}
			drawOverheadMap(surface);
			SDL_UpdateWindowSurface(window);
		}
        SDL_DestroyWindow(window);
        SDL_Quit();
}

