#ifndef WOLF3D_H
#define WOLF3D_H

#include "../frameworks/SDL2.framework/Headers/SDL.h"
//#include "../frameworks/SDL2_image.framework/Versions/A/Headers/SDL_image.h"
//#include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
//#include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
//#include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include <stdbool.h>
# include <fcntl.h>
# include "../libft/includes/ft_printf.h"
# include <math.h>
# include "const.h"



typedef struct	s_map
{
	char		*map;
	int			w;
	int			h;
	int			minimap_width;
	int			minimap_height;
	t_point		mm_start;
	t_point		mm;
	t_point		mm_cube;
}				t_map;

typedef struct	s_player
{
	int			x; 
	int			y;
	int			size;
	double		fov;
	double		dir; //direction - куда смотрит, в радианах
	double		dist_to_canvas;
	double		angle_step;
	double		xmm;
	double		ymm;
	float		visibility; // то сколько видит игрок максимум
	float		distance[W]; // измеренное расстояние до стены
}				t_player;

typedef struct	s_double2
{
	double		x;
	double		y;
}				t_double2;

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
	
	double			*sin;
	double			*cos;
	double			*tan;
	double			*arcsin;
	double			*arccos;
	double			*arctan;
	double			*fishTable;
	double			*xStepTable;
	double			*yStepTable;
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
void init_sdl(t_map *map, t_player *player);
t_point	dot(int x, int y);
double arcToRad(double angle);
int raycast(void);
void drawOverheadMap(SDL_Surface *surface);
void debug_map(t_map *map);
void debug_player(t_player *p);
void drawRay(SDL_Surface *surface, int x, int y);
int	add_arc(double *arc, double to_add);
void drawCanvas(SDL_Surface *surface);

/*
** init.c
*/
int	init_tabs(void);
void	init_player(t_player *player, t_map *map);
int load_textures(SDL_Surface *dest);

//skaren
void    all_get_distance(t_map *map, t_player *player);
// void    get_distance(t_map *map, t_player *player, float y1, float x1, float cos_angle, int count_distance);
void	pseudo_3d(t_player *player);
double find_wall(double angle);
int fps(void);

#endif

