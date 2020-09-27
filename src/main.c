#include "../includes/wolf3d.h"

t_point	dot(int x, int y)
{
	t_point	new;

	new.x = x;
	new.y = y;
	return (new);
}

int	main()
{
	/*double arr[1000000];
	for (int i = 0; i < 1000000; i++)
		arr[i] = cos(i);
		*/
	init_map(&map);
	init_tabs();
	init_player(&p, &map);
	init_sdl(&map, &p);
	return (0);
}       

	int verticalGrid;        // horizotal or vertical coordinate of intersection
	int horizontalGrid;      // theoritically, this will be multiple of TILE_SIZE
								 // , but some trick did here might cause
								 // the values off by 1
	double distToNextVerticalGrid; // how far to the next bound (this is multiple of
	double distToNextHorizontalGrid; // tile size)
	int xIntersection;  // x and y intersections
	int yIntersection;
	double distToNextXIntersection;
	double distToNextYIntersection;

	int xGridIndex;        // the current cell that the ray is in
	int yGridIndex;

	double distToVerticalGridBeingHit;      // the distance of the x and y ray intersections from
	double distToHorizontalGridBeingHit;      // the viewpoint

	int castArc, castColumn;

	double xtemp;
	int debug = 1;

