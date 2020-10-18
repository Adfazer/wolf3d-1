#ifndef WOLF3D_H
#define WOLF3D_H

# include "../frameworks/SDL2.framework/Headers/SDL.h"
// #include "../frameworks/SDL2_image.framework/Versions/A/Headers/SDL_image.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include <stdbool.h>
# include <fcntl.h>
# include "../libft/includes/ft_printf.h"
# include <math.h>
# include "const.h"
# include "colors.h"
# include "errors.h"



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

typedef struct	s_float2
{
	float		x;
	float		y;
}				t_float2;

typedef struct		s_distance
{
	float			dist;
	char			tex;
	int				offsetx;
	t_float2		coords;
	int				side;
	int				y;
}					t_distance;

typedef struct	s_player
{
	float		x; 
	float		y;
	float		speed;
	int			size;
	float		fov;
	float		dir;
	float		dist_to_canvas;
	float		step;
	int			floor_offset;
	t_distance	*distance[W];
}				t_player;

typedef	struct	s_coin
{
	float		angle;
	float		dist;
	float		temp_1;
	float		temp_2;
	float		temp_3;
	float		temp_4;
	float		temp_5;
	int			i;
	int			flag_1;
	int			flag_2;
	int			flag_i;
	int			count;
	SDL_Rect	cut_vertical_img;
	SDL_Rect	img_location;
}				t_coin;

typedef struct	s_bonus
{
	int			music_flag; // включает музыку
	Mix_Music	*music;
	Mix_Chunk	*music_guns;
	Mix_Chunk	*music_coin;
	int			fps;
	Uint32		startTime;
	int			fps_count;
	int			guns_fire;
	SDL_Surface *image_1;
	SDL_Surface *image_2;
	SDL_Surface *image_3;
	SDL_Surface *image_4;
	SDL_Surface *image_5;
	SDL_Surface *image_coin;
	t_float2	coint_pos;
	int			score_coin;
	SDL_Rect	imgLocation;
	int 		flag_guns;
	Uint32		start_guns;
	TTF_Font*	my_font;
}				t_bonus;

typedef struct		s_sdl
{
	SDL_Surface		*scrs;
	SDL_Surface		*textures;
	SDL_Surface		*sky;
	SDL_Surface		*icon;
	SDL_Renderer	*rend;
	SDL_Window		*win;
	int				tex_arr[0xff];
	const Uint8		*state;
	SDL_Event		e;
	int				skybox_offset;
	int				run;
	int				sides_mode;
}					t_sdl;

typedef struct	s_wolf
{
	t_map		*map;
	t_player	*player;
	t_sdl		*sdl;
	SDL_Surface	*surface;
	t_bonus		*bon;
}				t_wolf;



void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void draw_line(SDL_Surface *surface, t_point start, t_point end, int color);
void	draw_rectangle(SDL_Surface *surface, t_point start, t_point width_height,int color);
void wolf_loop(t_wolf *wolf);
t_point	dot(int x, int y);
int raycast(void);
void draw_minimap(t_wolf *wolf, t_map *map, t_player *p);
void debug_map(t_map *map);
void debug_player(t_player *p);
void draw_ray(t_wolf *wolf, float player, int x, int y);
int	add_arc(float *arc, float to_add);
void drawCanvas(SDL_Surface *surface);
int is_angle(float angle, float rad);
void draw_background(SDL_Surface *surface);
Uint32 getpixel(SDL_Surface *surface, int x, int y);

int	max(int a, int b);
int	float_is_equal(float a, float b);
void	init_tex_arr(t_wolf *wolf);


/*
** map.c
*/
void		init_mm(t_map *map);
void		init_map(t_wolf *wolf, char *b);

/*
** error.q
*/
int			error_free_s(t_wolf *wolf, char *s);
int			error(t_wolf *wolf, const char *s);
int			error_inv_c(t_wolf *wolf, char *s, char inv_char);
int			error_inv_n(t_wolf *wolf, char *s, int inv_num);

/*
** init.c
*/

void	init_player(t_player *player, t_map *map);
int load_textures(t_wolf *wolf, t_sdl *sdl);

/*
** distance.c
*/
t_distance *find_vertical_intersection(t_wolf *wolf, float angle, char texture);
t_distance *find_horizontal_intersection(t_wolf *wolf, float angle);
t_distance *dist_to_wall(t_wolf *wolf, float angle);
t_distance *dist_to_floor(t_wolf *wolf, float angle);
t_distance *dist_to_texture(t_wolf *wolf, float angle, char texture);
t_distance *t_distance_new(t_wolf *wolf);

//skaren
void    all_get_distance(t_wolf *wolf);
// void    get_distance(t_map *map, t_player *player, float y1, float x1, float cos_angle, int count_distance);
void	pseudo_3d(t_wolf *wolf, t_player *player, SDL_Surface *surface);


int fps(void);
int		is_texture(t_map *map, int x, int y, char texture);
t_distance	t_distance_dummy(float angle);
t_distance other_dummy(float angle);
void	music(t_bonus *bon);
void    render_fps(t_wolf *wolf, t_bonus *bon);
void    guns_shot(SDL_Surface *screen, int flag, t_bonus *bon);
void	init_bonus(t_bonus *bon);
void	render_shot(t_wolf *wolf, SDL_Surface *surface);
void	render_coin(t_wolf *wolf, SDL_Surface *surface);
void    render_score_coin(t_wolf *wolf);

int	add_floor_offset(int *offset, int to_add);

#endif

