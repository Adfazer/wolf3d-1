#ifndef WOLF3D_H
#define WOLF3D_H

#include "../frameworks/SDL2.framework/Headers/SDL.h"
// #include "../frameworks/SDL2_image.framework/Versions/A/Headers/SDL_image.h"
#include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
#include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
#include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include <stdbool.h>
# include <fcntl.h>
# include "../libft/includes/ft_printf.h"
# include <math.h>
# include "const.h"
# include "colors.h"



typedef struct	s_map
{
	char		*map;
	int			w;
	int			h;
	int			w_pix;
	int			h_pix;
	t_point		mm_start;
	int			mm_cube;
	int			mm_show;
	int			mm_w;
	int			mm_h;
	int			mm_p_size;
	float		mm_map_coef;
	float		mm_cube_coef;
	int			player_start;
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
	t_distance	distance[W]; // измеренное расстояние до стены
	t_point		*ray_coord[W];
	int			sides; //режим сторон света, будет в t_wolf
}				t_player;

typedef struct	s_bonus
{
	int			music_flag; // включает музыку
	Mix_Music	*music;
	int			fps;
	int			guns_fire;

	SDL_Surface *image_1;
	SDL_Surface *image_2;
	SDL_Surface *image_3;
	SDL_Surface *image_4;
	SDL_Surface *image_5;
	SDL_Rect	imgLocation;

	TTF_Font*	my_font;
}				t_bonus;

typedef struct	s_float2
{
	float		x;
	float		y;
}				t_float2;

typedef struct		s_sdl
{
	SDL_Surface		*scrs;
	SDL_Surface		*textures;
	SDL_Surface		*sky;
	SDL_Renderer	*rend;
	SDL_Window		*win;
	SDL_Texture		*win_texture;
	SDL_Event		e;
	unsigned char	*bytes;
	unsigned char	*bytes_texture;
	int				pitch;
	int				skybox_offset;
}					t_sdl;

typedef struct	s_wolf
{
	t_map		*map;
	t_player	*player;
	t_sdl		*sdl;
	SDL_Surface	*surface;
	t_bonus		*bon;
}				t_wolf;

int		error(char *s);
void		init_map(t_map *map, char *b);

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void draw_line(SDL_Surface *surface, t_point start, t_point end, int color);
void	draw_rectangle(SDL_Surface *surface, t_point start, t_point width_height,int color);
int		color_to_hex(int r, int g, int b);
void init_sdl(t_wolf *wolf, t_map *map, t_player *player);
t_point	dot(int x, int y);
int raycast(void);
void draw_minimap(SDL_Surface *surface, t_map *map, t_player *p);
void debug_map(t_map *map);
void debug_player(t_player *p);
void draw_ray(SDL_Surface *surface, float player, int x, int y);
int	add_arc(float *arc, float to_add);
void drawCanvas(SDL_Surface *surface);
int is_angle(float angle, float rad);
void draw_background(SDL_Surface *surface);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
int	get_color(Uint32 pixel, SDL_PixelFormat *format);
int	max(int a, int b);

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
void	music(t_bonus *bon);
void    render_fps(int fps, SDL_Surface *screen, t_bonus *bon);
void    guns_shot(SDL_Surface *screen, int flag, t_bonus *bon);
void	bonus_init(t_bonus *bon);

#endif

