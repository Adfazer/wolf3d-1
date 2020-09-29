#include "../includes/wolf3d.h"

void	init_player(t_player *p, t_map *map)
{
	ft_bzero(p, sizeof(t_player));
	p->x = 100;
	p->y = 100;
	
	p->xmm = p->x / map->mm.x + map->mm_start.x;
	p->ymm = p->y / map->mm.y + map->mm_start.y;
	//ft_printf("%d %d %f\n", p->x, map->mm.x, p->xmm);
	//ft_printf("%d %d\n", p->xmm,  p->ymm);
	p->fov = RAD_60;
	p->dir = RAD_90;
	p->size = 20;
	p->dist_to_canvas = (W / 2) / tan(RAD_60 / 2);
	p->angle_step = p->fov / W;
	// p->visibility = 512.0f;
}

int	init_tabs(void)
{	

	t.frameRate = 24;
	t.PROJECTIONPLANEWIDTH = 320;
	t.PROJECTIONPLANEHEIGHT = 200;
	t.TILE_SIZE = 64;
	t.WALL_HEIGHT = 64;
	//init_sdl();
	a.a60 = t.PROJECTIONPLANEWIDTH;
	a.a30 = floorf(a.a60 / 2);
	a.a15 = floorf(a.a30 / 2);
	a.a90 = floorf(a.a30 * 3);
	a.a180 = floorf(a.a90 * 2);
	a.a270 = floorf(a.a90 * 3);
	a.a360 = floorf(a.a90 * 4);
	a.a0 = 0;
	a.a5 = floorf(a.a15 / 3);
	a.a10 = floorf(a.a5 * 2);
	a.a45 = floorf(a.a15 * 3);

	t.sin = (float *)malloc(sizeof(float) * (a.a360 + 1));
	t.cos = (float *)malloc(sizeof(float) * (a.a360 + 1));
	t.tan = (float *)malloc(sizeof(float) * (a.a360 + 1));
	t.arcsin = (float *)malloc(sizeof(float) * (a.a360 + 1));
	t.arccos = (float *)malloc(sizeof(float) * (a.a360 + 1));
	t.arctan = (float *)malloc(sizeof(float) * (a.a360 + 1));
	t.fishTable = (float *)malloc(sizeof(float) * (a.a360 + 1));
	t.xStepTable = (float *)malloc(sizeof(float) * (a.a360 + 1));
	t.yStepTable = (float *)malloc(sizeof(float) * (a.a360 + 1));
	
	int i;
	i = -1;
	float radian;
	while (++i < a.a360)
	{
		
		radian = arcToRad(i) + 0.0001;
		t.sin[i] = sinf(radian);
		t.cos[i] = cosf(radian);
		t.tan[i] = tanf(radian);
		t.arcsin[i] = 1. / t.sin[i];
		t.arccos[i] = 1. / t.cos[i];
		t.arctan[i] = 1. / t.tan[i];

		t.xStepTable[i] = t.TILE_SIZE / t.tan[i];
		if (i >= a.a90 && i < a.a270)
		{
			if (t.xStepTable[i] > 0)
				t.xStepTable[i] *= -1;
		}
		else
		{
			if (t.xStepTable[i] < 0)
				t.xStepTable[i] *= -1;
		}
		
		t.yStepTable[i] = t.TILE_SIZE * t.tan[i];
		if (i >= a.a0 && i < a.a180)
		{
			if (t.yStepTable[i] < 0)
				t.yStepTable[i] *= -1;
		}
		else
		{
			if (t.yStepTable[i] > 0)
				t.yStepTable[i] *= -1;
		}

		for (int j = -a.a30; j <= a.a30; j++)
		{
			radian = arcToRad(j);
			t.fishTable[j + a.a30] = (1. / cosf(radian));
		}
	}
	return 0;
}