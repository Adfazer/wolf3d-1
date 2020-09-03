#include "../includes/wolf3d.h"

typedef struct	s_angles
{
	a0;
	a60;
	a30;
	a15;
	a90;
	a180;
	a360;
	a270;
	a5;
	a10;
	a45;
	
}				t_angles;

typedef struct	s_t
{
	
	float			sin[360];
	float			cos[360];
	float			tan[360];

}				t_t;

int main (void) {
    
	t_t t;
	t_map map;

	//init_sdl();

	init_map(&map);

	
	
    

    return 0;
}
