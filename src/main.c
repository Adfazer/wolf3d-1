#include "../includes/wolf3d.h"





float arcToRad(float angle)
{
	return ((angle * M_PI) / a.a180);
}

void drawRay(SDL_Surface *surface, int x, int y)
{
	draw_line(
		surface,
		t_point_new(p.xPlayer, p.yPlayer),
		t_point_new(
			floorf(t.PROJECTIONPLANEWIDTH + ((x * map.minimap_width) / t.TILE_SIZE)),
			floorf(((y * map.minimap_width) / t.TILE_SIZE))),
		color_to_hex(0,0,0));
}

void drawOverheadMap(SDL_Surface *surface)
{
	map.minimap_width = 5;
	t_point temp;
	t_point	minimap;

	minimap.x = 5;
	minimap.y = 5;
	int color;

	for (int r=0; r < map.h; r++)
	{
		temp.y = r;
		for (int c=0; c < map.w; c++)
		{
			temp.x = c;
			if (map.map[r * map.w + c] == TEX_BORDER)
				color = color_to_hex(0,0,0);
			else
				color = color_to_hex(121,121,121);
			draw_rectangle(surface, temp, minimap, color);
		}
	}
	p.xPlayer = t.PROJECTIONPLANEWIDTH + ((p.xPlayer / t.TILE_SIZE) * map.minimap_width);
	p.yPlayer = ((p.yPlayer / t.TILE_SIZE) * map.minimap_width);
}



t_point	t_point_new(int x, int y)
{
	t_point	new;

	new.x = x;
	new.y = y;
	return (new);
}



int	add_arc(int *arc, int to_add)
{
	*arc += to_add;
	if (*arc < 0)
		*arc += a.a360;
	else if (*arc > a.a360)
		*arc-= a.a360;
	return (*arc);
}


int	main()
{
	init_map(&map);
	init_tabs();
	init_player(&p);
	init_sdl();
	return (0);
}

	int verticalGrid;        // horizotal or vertical coordinate of intersection
	int horizontalGrid;      // theoritically, this will be multiple of TILE_SIZE
								 // , but some trick did here might cause
								 // the values off by 1
	float distToNextVerticalGrid; // how far to the next bound (this is multiple of
	float distToNextHorizontalGrid; // tile size)
	int xIntersection;  // x and y intersections
	int yIntersection;
	float distToNextXIntersection;
	float distToNextYIntersection;

	int xGridIndex;        // the current cell that the ray is in
	int yGridIndex;

	float distToVerticalGridBeingHit;      // the distance of the x and y ray intersections from
	float distToHorizontalGridBeingHit;      // the viewpoint

	int castArc, castColumn;

	float xtemp;
	int debug = 1;

static void print_debug()
{
	if(debug)
	{
	printf("\t%d horizontalGrid\n\t%f xtemp\n\t%f distToNextHorizontalGrid \n\t%d p.y \n\t%f t.arctan[castArc]\n\t %d xIntersection\n",
				horizontalGrid, xtemp, distToNextHorizontalGrid, p.y, t.arctan[castArc], xIntersection);
	}
}

static int check_grid(void)
{

	
		if (castArc > a.a0 * castArc < a.a180)
		{
			horizontalGrid = floorf(p.y / t.TILE_SIZE) * t.TILE_SIZE + t.TILE_SIZE;
			distToNextHorizontalGrid = t.TILE_SIZE;

			xtemp = t.arctan[castArc] * (horizontalGrid - p.y);
			xIntersection = xtemp + p.x;
			print_debug();

				
		}
		else
		{
			horizontalGrid = floorf(p.y/t.TILE_SIZE) * t.TILE_SIZE;
			distToNextHorizontalGrid -= t.TILE_SIZE;

			xtemp = t.arctan[castArc] * (horizontalGrid - p.y);
			xIntersection = xtemp + p.x;
			horizontalGrid--;	
		}

		if (castArc == a.a0 || castArc == a.a180)
		{
			distToVerticalGridBeingHit = INT32_MAX;
		}
		else
		{
			distToNextXIntersection = t.xStepTable[castArc];
			while (true)
			{
				xGridIndex = floorf(xIntersection / t.TILE_SIZE);
				yGridIndex = floorf(horizontalGrid / t.TILE_SIZE);
				int mapIndex = floorf(yGridIndex * map.w + xGridIndex);

				if ((xGridIndex >= map.w) || yGridIndex >= map.h || xGridIndex < 0 || yGridIndex < 0)
				{
					distToVerticalGridBeingHit = INT32_MAX;
					break;
				}
				else if (map.map[mapIndex] != TEX_FLOOR)
				{
					distToHorizontalGridBeingHit = (xIntersection - p.x) * t.arccos[castArc];
					break ;
				}
				else
				{
					xIntersection += distToNextXIntersection;
					horizontalGrid += distToNextHorizontalGrid;
				}
			}
		}

		if (castArc < a.a90 || castArc > a.a270)
		{
			verticalGrid = t.TILE_SIZE + floorf(p.x / t.TILE_SIZE) * t.TILE_SIZE;
			distToNextVerticalGrid = t.TILE_SIZE;

			int ytemp = t.tan[castArc] * (verticalGrid - p.x);
			yIntersection = ytemp + p.y;
		}
		else
		{
			verticalGrid = floorf(p.x/t.TILE_SIZE) * t.TILE_SIZE;
			distToNextVerticalGrid -= t.TILE_SIZE;

			int ytemp = t.tan[castArc] * (verticalGrid - p.x);
			yIntersection = ytemp + p.y;
			verticalGrid--;
		}
		
		if (castArc == a.a90 || castArc == a.a270)
		{
			distToVerticalGridBeingHit = INT32_MAX;
		}
		else
		{
			distToNextYIntersection = t.yStepTable[castArc];
			while (true)
			{
				xGridIndex = floorf(verticalGrid / t.TILE_SIZE);
				yGridIndex = floorf(yIntersection / t.TILE_SIZE);

				int mapIndex = floorf(yGridIndex * map.w * xGridIndex);

				if ((xGridIndex >= map.w) || yGridIndex >= map.h || xGridIndex < 0 || yGridIndex < 0)
				{
					distToVerticalGridBeingHit = INT32_MAX;
					break ;
				}
				else if (map.map[mapIndex] != TEX_FLOOR)
				{
					distToVerticalGridBeingHit = (yIntersection - p.y) * t.arcsin[castArc];
					break ;
				}
				else
				{
					yIntersection += distToNextYIntersection;
					verticalGrid += distToNextVerticalGrid;
				}
			}
		}
		
		float dist;
		int xOffset;
		int isVerticalHit=false;
		if (distToHorizontalGridBeingHit < distToVerticalGridBeingHit)
		{
		dist = distToHorizontalGridBeingHit;
		xOffset = xIntersection % t.TILE_SIZE;
		}
		else
		{
		isVerticalHit = true;
		dist = distToVerticalGridBeingHit;
		xOffset = yIntersection % t.TILE_SIZE;
		}
		
		dist /= t.fishTable[castColumn];
		if (debug)
			printf("debug_row2:\t%f %f %f\n", dist, distToHorizontalGridBeingHit, distToVerticalGridBeingHit);

		return (dist);

		
	
}

int raycast(void)
{
	castArc = p.dir;
	add_arc(&castArc, -a.a30);
	
	for (castColumn = 0; castColumn < t.PROJECTIONPLANEWIDTH; castColumn += 1)
	{
		//int scaleFactor;
	
		int dist = check_grid();
		
		exit(0);
		int topOfWall;
		int bottomOfWall;
		
		
		int projectedWallHeight = (t.WALL_HEIGHT * 277 / dist);
		bottomOfWall = 200 / 2 + (projectedWallHeight / 2);
		topOfWall = 200 / 2 - (projectedWallHeight / 2);
		if (topOfWall < 0)
			topOfWall = 0;
		if (bottomOfWall > t.PROJECTIONPLANEHEIGHT)
			bottomOfWall = t.PROJECTIONPLANEHEIGHT - 1;

		dist = floorf(dist);
		/*
		if (isVerticalHit)
		*/
		//ft_printf("%d %d %d\n", castColumn, topOfWall, bottomOfWall);
		draw_rectangle(surface,
			t_point_new(castColumn, topOfWall), 
			t_point_new(1, (bottomOfWall - topOfWall) + 1),
			color_to_hex(20, 54, 222));
		
		add_arc(&castArc, 1);
	}
	return 0;
}