#include "wolf3d.h"

void drawRay(SDL_Surface *surface, int x, int y)
{
	int dx0 = cos(p.dir) * CUBE;
	int dy0 = sin(p.dir) * CUBE;
	draw_line(
		surface,
		dot(x, y),
		dot(x + dx0, y - dy0),
		color_to_hex(255, 255, 255));
	/*
	int dx0 = cos(p.dir - RAD_60 / 2) * CUBE;
	int dy0 = sin(p.dir - RAD_60 / 2) * CUBE;
	int dx1 = cos(p.dir + RAD_60 / 2) * CUBE;
	int dy1 = sin(p.dir + RAD_60 / 2) * CUBE;
	
	draw_line(
		surface,
		dot(x, y),
		dot(x + dx0, y - dy0),
		color_to_hex(255, 255, 255));
		
	draw_line(
		surface,
		dot(x, y),
		dot(x + dx1, y - dy1),
		color_to_hex(255, 255, 255));
		*/
}

void drawBackground(SDL_Surface *surface)
{
	draw_rectangle(surface, dot(0,0), dot(W, H), 0);
}

static int	x_to_mm(int x)
{
	return map.mm_start.x + x / (map.mm.x);
}

static int	y_to_mm(int y)
{
	return map.mm_start.y + y / (map.mm.y);
}

void drawOverheadMap(SDL_Surface *surface)
{
	map.minimap_width = 5;
	int p_size = 20;
	drawBackground(surface);
	draw_rectangle(surface, map.mm_start,
	dot(map.mm_cube.x * map.w, map.mm_cube.y * map.h), 
	color_to_hex(121,121,121));

	for (int i = 0; i < map.h * map.w; i++)
	{
		if (map.map[i] == TEX_BORDER)
		{
			int xx = x_to_mm((i % map.w ) * CUBE);
			int yy = y_to_mm((i / map.h) * CUBE);
			draw_rectangle(surface, \
			dot(xx, yy),
			dot(CUBE / (map.mm.x), CUBE / (map.mm.y)), 0xbbbb00);
		}
	}

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

static int is_angle(float angle, float rad)
{
	//printf("%f\n", fabsf(cosf(angle) - cosf(rad)));
	return fabsf(cosf(angle) - cosf(rad)) < KLUDGE;
}

static double find_horizontal_intersection(double angle)
{
	t_point A;
	double diffy;
	double diffx;
	//find intersection with horizontal grid
	if (is_angle(angle, RAD_180) || is_angle(angle, RAD_0))
		return INT32_MAX;
	A.y = floorf((double)p.y / CUBE) * CUBE;
	A.y = angle > RAD_0 && angle < RAD_180 ? A.y - 1: A.y + CUBE;
	if (is_angle(angle, RAD_90))
	{
		A.x = p.x;
		diffx = 0;
	}
	else
	{
		A.x = p.x + (p.y - A.y) / tanf(angle);
		diffx = CUBE / tanf(angle);
	}
	diffy = angle > RAD_0 && angle < RAD_180 ? -CUBE : CUBE;
	
	// ft_printf("angle %f ax %d ay %d diffx %f diffy %f angle/rad90\n", angle, A.x, A.y, diffx, diffy);
	while (A.y >= 0 && A.y < H && A.x >= 0 && A.x < W)
	{
		//ft_printf("%d %d\n", A.x, A.y);
		if (map.map[(A.y / CUBE) * map.w + (A.x / CUBE)] == TEX_BORDER)
		{
			if (is_angle(angle, RAD_90))
				return (fabsf(p.y - A.y));
			return (fabs((p.x - A.x) / cosf(angle)));
		}
			
		A.x += diffx;
		A.y += diffy;
		// ft_printf("here\n");
	}
	return INT32_MAX;
}

static double find_vertical_intersection(double angle)
{
	t_point B;
	double diffy;
	double diffx;

	if (is_angle(angle, RAD_90))
		return INT32_MAX;

	B.x = floorf((double)p.x / CUBE) * CUBE;
	B.x = angle > RAD_270 || angle < RAD_90 ? B.x + CUBE : B.x - 1;

	if (is_angle(angle, RAD_0) || is_angle(angle, RAD_180))
	{
		B.y = p.y;
		diffy = 0;
	}
	else
	{
		B.y = p.y + (p.x-B.x)*tan(angle);
		diffy = CUBE * tanf(angle);
	}
	diffx = angle > RAD_270 || angle < RAD_90 ? -CUBE : CUBE;
	
	while (B.y >= 0 && B.y < H && B.x >= 0 && B.x < W)
	{
		//ft_printf("%d %d\n", B.x, B.y);
		if (map.map[(B.y / CUBE) * map.w + (B.x / CUBE)] == TEX_BORDER)
		{
			if (is_angle(angle, RAD_0) || is_angle(angle, RAD_180))
				return (fabsf(p.x - B.x));
			return (fabs((p.x - B.x) / cosf(angle)));
		}
			
		B.x += diffx;
		B.y += diffy;
	}
	return INT32_MAX;
}

double find_wall(double angle)
{
	double a = fminf(
		find_horizontal_intersection(angle),
		find_vertical_intersection(angle)
		);
	// ft_printf("%f\n", a);
	return a;
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

static void draw_canvas()
{
	int i;
	int j;
	double angle;
	int slice_height;
	int slice_top;

	i = -1;
	angle = p.fov / 2;
	while (++i < W)
	{
		slice_height = (H / find_wall(angle)) * p.dist_to_canvas;
		slice_top = W / 2 - slice_height / 2;
		ft_printf("%d %d \n", slice_top, slice_height);
		j = slice_top;
		while (j > slice_top - slice_height)
		{
			set_pixel(surface, dot(i, j--), 0x00ff00);
		}
		add_arc(&angle, p.angle_step);
	}
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
		drawOverheadMap(surface);
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
						p.x += CUBE;
						p.x = p.x > CUBE * map->w - 1? CUBE * map->w - 1 : p.x;
						//debug_player(player);
					}
					if (event.key.keysym.sym == SDLK_a)
					{
						p.x -= CUBE;
						p.x = p.x < 0 ? 0 : p.x;
						//debug_player(player);
					}
					if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
					{
						p.y += CUBE;
						p.y = p.y > CUBE * map->h - 1 ? CUBE * map->h - 1 : p.y;
					}
					if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
					{
						p.y -= CUBE;
						p.y = p.y < 0 ? 0 : p.y;
					}
					if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
					{
						if (event.key.keysym.sym == SDLK_RIGHT)
							add_arc(&p.dir, -RAD_45);
						if (event.key.keysym.sym == SDLK_LEFT)
							add_arc(&p.dir, RAD_45);
					}

				}
    		}
			
			//draw_canvas();
			// ft_printf("%f dist %f dir\n", find_wall(player->dir), p.dir);
			drawOverheadMap(surface);
			all_get_distance(map, player);
			pseudo_3d(player);
			drawRay(surface, p.x / map->mm.x + map->mm_start.x, p.y / map->mm.y + map->mm_start.y);
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