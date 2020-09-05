#include "../includes/wolf3d.h"

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



float arcToRad(float angle)
{
	return ((angle * M_PI) / a.a180);
}

t_t t;
t_angles a;
t_map map;
t_player p;

void drawOverheadMap(void)
{
	map.minimap_width = 5;

	for (int r=0; r < H; r++)
	{
		for (int c=0; c < W; c++)
		{
			//drawRectangle;
			;
		}
	}
	p.xPlayer = t.PROJECTIONPLANEWIDTH + ((p.xPlayer / t.TILE_SIZE) * map.minimap_width);
	p.yPlayer = ((p.yPlayer / t.TILE_SIZE) * map.minimap_width);
}
	


int init (void) {
    
	
	init_map(&map);

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

		for (i = -a.a30; i <= a.a30; i++)
		{
			radian = arcToRad(i);
			t.fishTable[i + a.a30] = (1. / cosf(radian));
		}
	}

	

	
	
    

    return 0;
}


int	main()
{
	return 0;
}