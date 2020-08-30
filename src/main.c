#include "../includes/wolf3d.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_START_POS_X = 100;
const int SCREEN_START_POS_Y = 100;

int		error(char *s)
{
	ft_printf("%s\n", s);
	exit(1);
}

/*
static void init_sdl(void)
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
        printf("error\n");
        exit(1);
    }    
    SDL_Window* window = NULL;
    window = SDL_CreateWindow("Hello, SDL 2!", 100, 
                                100, SCREEN_WIDTH, SCREEN_HEIGHT, 
                                SDL_WINDOW_SHOWN);
    if (!window)
        printf("window error\n");

    SDL_Surface* screen_surface = NULL;
    screen_surface = SDL_GetWindowSurface(window);
    
        SDL_FillRect(screen_surface, NULL, SDL_MapRGB( screen_surface->format, 0, 255, 0));
        SDL_UpdateWindowSurface(window);    

        //SDL_Delay(5000);
         bool isquit = false;
		SDL_Event event;
		while (!isquit) {
			if (SDL_PollEvent( & event)) {
				if (event.type == SDL_QUIT) {
					isquit = true;
        }
    }
}
        SDL_DestroyWindow(window);

        SDL_Quit();
}
*/
void	init_player(t_player *player)
{
	player->x = 96;
	player->y = 224;
	player->fov = 60;
	player->dir = 60;
	int i = -1;
	while (++i < 360)
	{
		player->sin[i] = sinf(i * M_PI / 180);
		player->cos[i] = cosf(i * M_PI / 180);
		player->tan[i] = tanf(i * M_PI / 180);
	}

}

bool	is_ray_faced_up(float dir)
{
	return (dir >= 0. && dir < 180.);
}

t_float2	find_nearest_horiz(t_player p, t_map *map)
{
	t_float2 a;
	int y_a = 0;
	int x_a = 0;

	
	a.y = floor(p.y / CUBE) * CUBE;
	a.y =  is_ray_faced_up(p.dir) ? a.y - 1 : a.y + CUBE;
	a.x = p.x + (p.y - a.y) / p.tan[p.dir];
	y_a = is_ray_faced_up(p.dir) ? -CUBE : CUBE;
	x_a = CUBE / p.tan[p.dir];
	
	
	while (map->map[(int)a.x / CUBE + ((int)a.y / CUBE) * map->w] != TEX_BORDER)
	{
		
		a.y += y_a;
		a.x += x_a;
		
	}
	return a;
}

bool	is_ray_faced_right(float dir)
{
	return (dir > 270. || dir <= 90.);
}

t_float2	find_nearest_vert(t_player p, t_map *map)
{
	t_float2 a;
	int y_a = 0;
	int x_a = 0;

	a.x = p.x;
	a.y = p.y;
	
	a.x = floor(p.x / CUBE) * CUBE;
		a.x =  is_ray_faced_right(p.dir) ? a.x + CUBE : a.x - 1;
		a.y = p.y + (p.x - a.x) / p.tan[p.dir];
		
		x_a = is_ray_faced_right(p.dir) ? CUBE : -CUBE;
		y_a = CUBE * p.tan[p.dir];
		ft_printf("%f %f %d %d\n", a.x, a.y, (int)a.x / CUBE, (int)a.y / CUBE);
		ft_printf("P %f %f %d %d\n", p.x, p.y, (int)p.x / CUBE, (int)p.y / CUBE);
	while (map->map[(int)a.x / CUBE + ((int)a.y / CUBE) * map->w] != TEX_BORDER)
	{
		
		a.y += y_a;
		a.x += x_a;
		
		

	}
	return a;
}

void find_nearest_wall(t_player p, t_map *map)
{
	t_float2 vert = find_nearest_vert(p, map);
	t_float2 horiz = find_nearest_horiz(p, map);

	float dist_v = fabsf(p.x - vert.x) / p.cos[p.dir];
	float dist_h = fabsf(p.y - horiz.y) / p.cos[p.dir];
	t_float2 a = dist_v >= dist_h ?  horiz : vert;
	
	//int x = (int)a.x / CUBE + ((int)a.y / CUBE) * map->w;
	
	ft_printf("%f %f %d %d\n", a.x, a.y, (int)a.x / CUBE, (int)a.y / CUBE);
	

}

int main (void) {
    
	t_player player;
	t_map map;

	init_player(&player);
	init_map(&map);
	find_nearest_wall(player, &map);
	//
	//init_sdl();
    

    return 0;
}
