#include "../includes/wolf3d.h"

void	init_player(t_player *p, t_map *map)
{
	ft_bzero(p, sizeof(t_player));
	p->size = 10;
	p->x = CUBE * (map->player_start % map->w) + p->size;
	p->y = CUBE * (map->player_start / map->w) + p->size;
	p->speed = 10.0;
	p->fov = RAD_60;
	p->dir = RAD_270;
	p->size = 10;
	p->dist_to_canvas = (W / 2) / tan(p->fov / 2);
	p->step = p->fov / W;
	p->sides = 1;
}

void	bonus_init(t_bonus *bon)
{
	bon->music_flag = 0;
	bon->fps = 1;
	bon->guns_fire = 0;
	bon->music = NULL;
	bon->image_1 = IMG_Load("textures/guns-1.bmp");
	bon->image_2 = IMG_Load("textures/guns-2.bmp");
	bon->image_3 = IMG_Load("textures/guns-3.bmp");
	bon->image_4 = IMG_Load("textures/guns-4.bmp");
	bon->image_5 = IMG_Load("textures/guns-5.bmp");
	bon->my_font = TTF_OpenFont("ttf/19888.ttf", 14);
	
	bon->imgLocation.w = W / 3;
    bon->imgLocation.h = H / 3;
    bon->imgLocation.x = (W / 2) - (W / 6);
    bon->imgLocation.y = H - H / 3;
}