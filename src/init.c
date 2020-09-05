#include "../includes/wolf3d.h"

void	init_player(t_player *p)
{
	p->x = 80;
	p->y = 80;
	p->fov = a.a60;
	p->dir = 0;
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