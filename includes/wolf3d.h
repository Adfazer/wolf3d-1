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

# define W_W 512
# define W_H 512
# define CUBE 64

typedef struct	s_map
{
	char		*map;
	int			w;
	int			h;
}				t_map;

typedef struct	s_player
{
	int			x;
	int			y;
	float		fov;
	int		dir;
	float			sin[360];
	float			cos[360];
	float			tan[360];
}				t_player;

typedef struct	s_float2
{
	float		x;
	float		y;
}				t_float2;

int		error(char *s);
void		init_map(t_map *map);

#endif

