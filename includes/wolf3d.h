#ifndef WOLF3D_H
#define WOLF3D_H

#include "../frameworks/SDL2.framework/Headers/SDL.h"
//#include "../frameworks/SDL2_image.framework/Versions/A/Headers/SDL_image.h"
//#include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
//#include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
#include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
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

typedef struct		s_distance
{
	float			dist;
	char			tex;
	int				offsetx;
}					t_distance;

typedef struct	s_player
{
	float		x; 
	float		y;
	float		speed;
	int			size;
	float		fov;
	float		dir; //direction - куда смотрит, в радианах
	float		dist_to_canvas;
	float		step;
	float		xmm;
	float		ymm;
	float		view_dist;
	t_distance	distance[W]; // измеренное расстояние до стены
	t_point		*ray_coord[W];
	int			sides; //режим сторон света, будет в t_wolf

	int			music_flag; // включает музыку
	Mix_Music	*music;


}				t_player;


typedef struct	s_float2
{
	float		x;
	float		y;
}				t_float2;

typedef struct		s_sdl
{
	SDL_Surface		*scrs;
	SDL_Surface		*textures;
	SDL_Surface		**arr;
	SDL_Renderer	*rend;
	SDL_Window		*win;
	SDL_Texture		*win_texture;
	SDL_Event		e;
	int				y;
	unsigned char	*bytes;
	unsigned char	*bytes_texture;
	int				pitch;
	bool			run;
}					t_sdl;

typedef struct	s_wolf
{
	t_map		*map;
	t_player	*player;
	t_sdl		*sdl;
	SDL_Surface	*surface;
}				t_wolf;

/*
t_map map;
t_player p;
SDL_Surface* surface;
*/

int		error(char *s);
void		init_map(t_map *map);

void set_pixel(SDL_Surface *surface, t_point point, Uint32 pixel);
void draw_line(SDL_Surface *surface, t_point start, t_point end, int color);
void	draw_rectangle(SDL_Surface *surface, t_point start, t_point width_height,int color);
int		color_to_hex(int r, int g, int b);
void init_sdl(t_wolf *wolf, t_map *map, t_player *player);
t_point	dot(int x, int y);
int raycast(void);
void draw_minimap(SDL_Surface *surface, t_map *map, t_player *p);
void debug_map(t_map *map);
void debug_player(t_player *p);
void drawRay(SDL_Surface *surface, t_player *player, int x, int y);
int	add_arc(float *arc, float to_add);
void drawCanvas(SDL_Surface *surface);
int is_angle(float angle, float rad);
void draw_background(SDL_Surface *surface);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
int	get_color(Uint32 pixel, SDL_PixelFormat *format);

/*
** init.c
*/

void	init_player(t_player *player, t_map *map);
int load_textures(t_wolf *wolf, t_sdl *sdl);

//skaren
void    all_get_distance(t_map *map, t_player *player);
// void    get_distance(t_map *map, t_player *player, float y1, float x1, float cos_angle, int count_distance);
void	pseudo_3d(t_wolf *wolf, t_player *player, SDL_Surface *surface);
t_distance dist_to_wall(t_player *p, t_map *map, float angle);
t_distance dist_to_floor(t_player *p, t_map *map, float angle);
t_distance dist_to_texture(t_player *p, t_map *map, float angle, char texture);
int fps(void);
int		is_texture(t_map *map, float x, float y, char texture);
t_distance	t_distance_dummy(float angle);
t_distance other_dummy(float angle);
void	music(t_player *player);

#endif

