#ifndef WOLF3D_H
#define WOLF3D_H

#include "../frameworks/SDL2.framework/Headers/SDL.h"
//#include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
//#include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
//#include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include <stdbool.h>
# include <fcntl.h>
# include "../libft/includes/ft_printf.h"
# include <math.h>

# define CHARSET " *012S"
# define INTBUF_INIT_SIZE 64
# define INTBUF_RESIZE_COEF 4
# define MAP_MAX_SIZE 2048
# define MAP_MIN_SIZE 16
# define MAP_MIN_ROW_NUM 3
# define MAP_MIN_COL_NUM 4
# define MAP_FILEPATH "map.txt"

# define TEX_BORDER '*'
# define TEX_FLOOR ' '

# define W 512
# define H 512
# define CUBE 64

typedef struct	s_map
{
	char		*map;
	int			w;
	int			h;
	int			minimap_width;
	int			minimap_height;
}				t_map;

typedef struct	s_player
{
	int			x;
	int			y;
	int			size;
	float		fov;
	int			dir;
	float		xPlayer;
	float		yPlayer;
}				t_player;

typedef struct	s_float2
{
	float		x;
	float		y;
}				t_float2;

typedef struct	s_angles
{
	int a0;
	int a60;
	int a30;
	int a15;
	int a90;
	int a180;
	int a360;
	int a270;
	int a5;
	int a10;
	int a45;
	
}				t_angles;

typedef struct	s_t
{
	
	float			*sin;
	float			*cos;
	float			*tan;
	float			*arcsin;
	float			*arccos;
	float			*arctan;
	float			*fishTable;
	float			*xStepTable;
	float			*yStepTable;
	int				PROJECTIONPLANEWIDTH;
	int				PROJECTIONPLANEHEIGHT;
	int				TILE_SIZE;
	int				WALL_HEIGHT;
	int				frameRate;

}				t_t;

t_t t;
t_angles a;
t_map map;
t_player p;
SDL_Surface* surface;

int		error(char *s);
void		init_map(t_map *map);

void set_pixel(SDL_Surface *surface, t_point point, Uint32 pixel);
void draw_line(SDL_Surface *surface, t_point start, t_point end, int color);
void	draw_rectangle(SDL_Surface *surface, t_point start, t_point width_height,int color);
int		color_to_hex(int r, int g, int b);
void init_sdl(void);
t_point	dot(int x, int y);
float arcToRad(float angle);
int raycast(void);
void drawOverheadMap(SDL_Surface *surface);

/*
** init.c
*/
int	init_tabs(void);
void	init_player(t_player *player);

#endif

