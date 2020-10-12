#ifndef CONST_H
# define CONST_H

# define DEBUG 1
# define SHOW_FPS 0



# define INTBUF_INIT_SIZE 64
# define INTBUF_RESIZE_COEF 4
# define MAP_MAX_SIZE 2048
# define MAP_MIN_SIZE 16
# define MAP_MIN_ROW_NUM 3
# define MAP_MIN_COL_NUM 4
# define MAP_FILEPATH "maps/map.txt"

# define CHARSET " *#012S"
# define WALLSET "*#"
# define FLOORSET " S"
# define TEX_BORDER '*'
# define TEX_FLOOR ' '
# define TEX_WALL '#'
# define TEX_INF '8'  //возвращается с бесконечностью, не является текстурой
# define TEX_START 'S' 


# define W 512
# define H 512
# define CUBE 64

# define PLAYER_MM_SIZE 4
# define KLUDGE 0.0001
# define RAD_360 6.28319f
# define RAD_1 0.0174533f
# define RAD_60 1.047200f
# define RAD_30 0.523599f
# define RAD_180 M_PI
# define RAD_0 0.
# define RAD_90 1.570800f
# define RAD_45 0.785398f
# define RAD_270 4.71239f

# define TEXTURE_PATH "textures/tex.bmp"
# define ICON_PATH "textures/icon.bmp"
# define SKY_PATH "textures/sky.bmp"


# define RMASK 0x000000ff
# define GMASK 0x0000ff00
# define BMASK 0x00ff0000
# define AMASK 0xff000000


#endif