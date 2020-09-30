#include "wolf3d.h"



void set_pixel(SDL_Surface *surface, t_point point, Uint32 pixel)
{
  Uint32 *target_pixel = (Uint32 *)((Uint8 *)surface->pixels + point.y * surface->pitch
  	 + point.x * sizeof *target_pixel);
  *target_pixel = pixel;
}

static void rotate(SDL_Event *event, int *x)
{
	if (event->motion.xrel >= 0)
		add_arc(&p.dir, -0.02);
	else
		add_arc(&p.dir, 0.02);
	*x = event->motion.x;
	//debug_player(&p);
}


//работает, пускает в углы
void	calc_move(t_player *p, double dy, double dx)
{
	if (is_texture(p->x + dx, p->y, TEX_FLOOR))
		p->x += dx;
	if (is_texture(p->x, p->y + dy, TEX_FLOOR))
		p->y += dy;
}
//не работает
/*
void	calc_move(t_player *p, double dy, double dx, int key)
{
	float diffx;
	float diffy;
	double dir;

	dir = p->dir;
	if (key == SDLK_d)
		add_arc(&dir, -RAD_90);
	else if (key == SDLK_a)
		add_arc(&dir, RAD_90);
	else if (key == SDLK_s || key == SDLK_DOWN)
		add_arc(&dir, RAD_180);
	//diffy = dir > RAD_180 && dir < RAD_360 ? 0 : 1;
	//diffx = dir > RAD_270 || dir < RAD_90 ? 0 : 1;
	if ((int)p->x / CUBE != (int)(p->x + dx + diffx) / CUBE || (int)p->y / CUBE != (int)(p->y + dy + diffy) / CUBE)
	{
		diffx = 0;
		diffy = 0;
        float cx = 0.1;
        float cy = 0.1;
		float targetx = p->x + dx;
		float targety = p->y + dy;
        int i = -1;
        dx = 0;
        dy = 0;
        while (++i < fmaxf(dx,dy))
        {
        	if (is_texture(p->x + dx, p->y + dy, TEX_FLOOR))
			{
				dx += cx;
				dy += cy;
			}
        	else
			{
				dx -= cx;
				dy -= cy;
				break;
			}
        }
	}
	p->x += dx;
	p->y += dy;
}
*/

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
    
	Uint32 startTime = 0;
    Uint32 endTime = 0;
    Uint32 delta = 0;
    short fps = 60;
    short timePerFrame = 16; // miliseconds
    
    


    surface = NULL;
    
    surface = SDL_GetWindowSurface(window);
		draw_minimap(surface);
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
					rotate(&event, &x);
					//debug_player(player);
				}
				if (event.type == SDL_KEYDOWN)
				{
					isquit = event.key.keysym.sym == SDLK_ESCAPE ? true : isquit;
					if (event.key.keysym.sym == SDLK_d)
					{
						calc_move(&p, p.speed * sinf(p.dir + RAD_90), -(p.speed * cosf(p.dir + RAD_90)));
						//p.y += p.speed * sinf(p.dir + RAD_90);
						//p.x -= p.speed * cosf(p.dir + RAD_90);
						// p.x = p.x > CUBE * map->w - 1? CUBE * map->w - 1 : p.x;
						//debug_player(player);
					}
					if (event.key.keysym.sym == SDLK_a)
					{
						calc_move(&p, p.speed * sinf(p.dir - RAD_90), -(p.speed * cosf(p.dir - RAD_90)));
						//p.y += p.speed * sinf(p.dir - RAD_90);
						//p.x -= p.speed * cosf(p.dir - RAD_90);
						// p.x = p.x < 0 ? 0 : p.x;
						//debug_player(player);
					}
					if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
					{
						calc_move(&p, p.speed * sinf(p.dir), -(p.speed * cosf(p.dir)));
						//p.y += p.speed * sinf(p.dir);
						//p.x -= p.speed * cosf(p.dir);
						// p.y = p.y > CUBE * map->h - 1 ? CUBE * map->h - 1 : p.y;
					}
					if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
					{
						calc_move(&p, -(p.speed * sinf(p.dir)), p.speed * cosf(p.dir));
						//p.y -= p.speed * sinf(p.dir);
						//p.x += p.speed * cosf(p.dir);
						// p.y = p.y < 0 ? 0 : p.y;
					}
					if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
					{
						if (event.key.keysym.sym == SDLK_RIGHT)
							add_arc(&p.dir, -RAD_1);
						if (event.key.keysym.sym == SDLK_LEFT)
							add_arc(&p.dir, RAD_1);
					}

				}
    		}

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
			if (SHOW_FPS)
        		printf("FPS is: %i \n", fps);
		
        
        startTime = endTime;
        endTime = SDL_GetTicks();
			
			//draw_canvas();
			// ft_printf("%f dist %f dir\n", find_wall(player->dir), p.dir);
			
			draw_background(surface);
			all_get_distance(map, player);
			pseudo_3d(player);
			draw_minimap(surface);
			
			//printf("%f\n", find_wall(player->dir));
			// ft_printf("%f dist %f dir\n", find_wall(player->dir), p.dir);
			//draw_line(surface, dot(50,50), dot(10, 10), 0xFFFFFF);

			SDL_UpdateWindowSurface(window);
			
		}
        SDL_DestroyWindow(window);
        SDL_Quit();
}



/*
static void draw_wall(SDL_Surface *surface, double dist)
{
	surface += 1;
	dist += 1;
}
*/

/*
void drawCanvas(SDL_Surface *surface)
{
	double angle = p.dir;
	add_arc(&angle, RAD_60 / 2);
	double angle_increment = -RAD_60 / W;
	double dist;
	for (int i = 0; i < W; i++)
	{
		dist = find_wall(angle);
		draw_wall(surface, dist);
		add_arc(&angle, angle_increment);
	}
}
*/