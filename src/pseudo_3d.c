#include "../includes/wolf3d.h"

void	draw_column(t_wolf *wolf, SDL_Surface *surface, t_point point, t_distance *dist, int size, int height)
{
	int color;

	int i = 0;      
	while (point.y < size)
	{
		color = getpixel(wolf->sdl->textures, dist->offsetx + \
		wolf->sdl->tex_arr[dist->tex], i * CUBE / height);
		if (point.y > 0 && point.y < H)
			set_pixel(surface, point.x, point.y, color);
		point.y++;
		i++;
	}
}

void	draw_floor(t_wolf *wolf, SDL_Surface *surface, int x, int y)
{
	while (y < W)
	{
		set_pixel(surface, x, y, COLOR_GREY_LIGHT);
		y++;
	}	
}

void	draw_sky(t_wolf *wolf, int xtex, int x, int y)
{
	int		i;
	i = -1;
	
	while (++i < y)
	{
		set_pixel(wolf->surface, x, i, getpixel(wolf->sdl->sky, x + wolf->sdl->skybox_offset, i));
	}
}

void	floorcast(t_wolf *wolf, t_distance *dist, int x, int y, float dir)
{
	float curr_dist;
	float weight;
	float currFloorX;
	float currFloorY;
	int textx;
	int texty;
	int color;
	float ratio;
	float distance;
	float xend;
	float yend;
	float rowDistance;
	float x0, x1, y0, y1;
	float a0, a1;
	float floorStepX;
	float floorStepY;
	float floorX;
	float floorY;
	a0 = dir;
	a1 = dir;
	add_arc(&a0, RAD_30);
	add_arc(&a1, -RAD_30);
	y = dist->y;
	float floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall
	float mapX = floorf(wolf->player->x);
	float mapY =  floorf(wolf->player->y);
	float wallX;

	if (dist->side == 0)
	{
		wallX = dist->coords.x;
	}
	else
		wallX = dist->coords.y;
	wallX -= floorf(wallX);
	
	 /*
      //4 different wall directions possible
      if(dist->side == 0 && (wolf->player->dir < RAD_90 || wolf->player->dir > RAD_270))
      {
        floorXWall = mapX;
        floorYWall = mapY + wallX;
      }
      else if(dist->side == 0 && (wolf->player->dir > RAD_90 || wolf->player->dir < RAD_360))
      {
        floorXWall = mapX + 1.0;
        floorYWall = mapY + wallX;
      }
      else if(dist->side == 1 && wolf->player->dir < RAD_180)
      {
        floorXWall = mapX + wallX;
        floorYWall = mapY;
      }
      else
      {
        floorXWall = mapX + wallX;
        floorYWall = mapY + 1.0;
      }
*/
/*
      double distWall, distPlayer, currentDist;
	  if (y < 0)
	  	y = H;
		  
	while (y < H)
	{
		
      curr_dist = (float)H / (float)(2 * y - H);
		weight = curr_dist / (dist->dist);
		currFloorX = weight * floorXWall + (1.f - weight) * wolf->player->x;
		currFloorY = weight * floorYWall + (1.f - weight) * wolf->player->y;
		//printf("%d %d\n", tilex, tiley);
		textx = (int)(currFloorX * CUBE) % CUBE;
		texty = (int)(currFloorY * CUBE) % CUBE;
		if (textx < 0)
			textx = 0;
		if (texty < 0)
			texty = 0;
		color = getpixel(wolf->sdl->textures, textx + CUBE * 5, texty);
		set_pixel(wolf->surface, x, y, color);
		color = getpixel(wolf->sdl->textures, textx + CUBE * 5, texty);
		set_pixel(wolf->surface, x, H - y, color);
		y++;
	}
*/	
	/*
	distance = sqrtf(powf(wolf->player->dist_to_canvas, 2.) + W / 2 * W / 2);
	while (y < H / 2)
	{
		*/
		/*
		def Translate(X,Y,angle,distance):                #defines function
    dX = distance*math.cos(math.radians(angle))   #change in x 
    dY = distance*math.sin(math.radians(angle))   #change in y 
    Xfinal = X + dX                               
    Yfinal = Y + dY
    return Xfinal, Yfinal
	*/
		
		/*
		rowDistance = (float)H / (float)(2 * y - H);
		x0 = wolf->player->distance[W - 1]->coords.x;
		y0 = wolf->player->distance[W - 1]->coords.y;
		x1 = wolf->player->distance[0]->coords.x;
		y1 = wolf->player->distance[0]->coords.y;
		

		floorStepX = rowDistance * (x1 - x0) / W;
		floorStepY = rowDistance * (y1 - y0) / W;

		floorX = wolf->player->x + x0 * rowDistance;
		floorY = wolf->player->y + y0 * rowDistance;

		

		x = 0;
		while (x < W)
		{
			int cellX = (int)floorX;
			int cellY = (int)floorY;

			int tx = (int)(CUBE * (floorX - cellX)) & (CUBE - 1);
			int ty = (int)(CUBE * (floorY - cellY)) & (CUBE - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			color = getpixel(wolf->sdl->textures, tx, ty);
			set_pixel(wolf->surface, x, y, color);
			x++;
		}
		y++;
*/
		/*
		while (y < H)
		{	
		
		ratio = (float)(H / 2) / (float)(y - H / 2);
		distance = floorf((wolf->player->dist_to_canvas * ratio))  * dist->dist ; 
		xend = floorf(distance * sinf(dir)) + wolf->player->x;
		yend = floorf(distance * cosf(dir)) + wolf->player->y;
		//int cellx = (int)(xend / CUBE);
		//int celly = (int)(yend / CUBE);

		int tilex = (int)(yend) % CUBE;
		int tiley = (int)(xend) % CUBE;
		if (tilex < 0)
			tilex = 0;
		if (tiley < 0)
			tiley = 0;
		//printf("%d %d\n", tilex, tiley);
		color = getpixel(wolf->sdl->textures, tilex, tiley);
		set_pixel(wolf->surface, x, y, color);
		y++;
		}		
		*/

	/*
		if (dir < RAD_90 || dir > RAD_270)
		{
			dist->coords.x = floorf(wolf->player->x);
			dist->coords.y = floorf(wolf->player->y) + wallX;
		}
		else if(dir > RAD_90 && dir < RAD_270)
		{
			dist->coords.x = floorf(wolf->player->x) + 1.0f;
			dist->coords.y = floorf(wolf->player->y) + wallX;
		}
		else if(dir > 0 && dir < RAD_180)
		{
			dist->coords.x = floorf(wolf->player->x) + wallX;
			dist->coords.y = floorf(wolf->player->y);
		}
		else
		{
			dist->coords.x = floorf(wolf->player->x) + wallX;
			dist->coords.y = floorf(wolf->player->y) + 1.0f;
		}
	*/
	
	while (y < H)
	{	
		
		curr_dist = (float)H / (float)(2 * y - H);
		
		weight = (curr_dist) / (dist->dist);
		if (x == 100 && y == 400)
			printf("%f %f\n", dist->coords.x, dist->coords.y);
		currFloorX = weight * dist->coords.x + (1.f - weight) * ((int)wolf->player->x);
		currFloorY = weight * dist->coords.y + (1.f - weight) * ((int)wolf->player->y);
		//printf("%d %d\n", tilex, tiley);
		//if (x == 100 && y == 400)
		//	printf("%f %f\n", currFloorX, currFloorY);	
		textx = (int)(currFloorX * CUBE) % CUBE;
		texty = (int)(currFloorY * CUBE) % CUBE;
		
		if (textx < 0)
			textx = 0;
		if (texty < 0)
			texty = 0;
		color = getpixel(wolf->sdl->textures, textx + CUBE * 5, texty);
		set_pixel(wolf->surface, x, y, color);
		color = getpixel(wolf->sdl->textures, textx + CUBE * 5, texty);
		set_pixel(wolf->surface, x, H - y, color);
		y++;
	}
	
	
}


void	pseudo_3d(t_wolf *wolf, t_player *player, SDL_Surface *surface)
{
    t_point point;
    int     count_distance;
	float dir;
	float step;

	point.x = 0;
    point.y = 0;
	count_distance = W - 1; //номер луча с конца
	dir = player->dir;
	add_arc(&dir, player->fov / 2);
	step = player->fov / W;
	while (point.x < W)
	{
		if (player->distance[count_distance]->dist != 0)
		{
			point.y = ceilf((CUBE * player->dist_to_canvas) / player->distance[count_distance]->dist);
			point.y = (H - point.y) / 2;
			int height = H - point.y * 2;
			int temp = point.y;
			player->distance[count_distance]->y = H - point.y;
			draw_column(wolf, surface, point, player->distance[count_distance], H - point.y, height);
			draw_sky(wolf, (int)((dir / RAD_360) * wolf->sdl->sky->w),point.x, point.y);
			//floorcast(wolf, player->distance[count_distance], point.x, H - point.y, dir);
			draw_floor(wolf, surface, point.x, H - point.y);
		}
		count_distance--; // следующий луч
		point.x++;
		add_arc(&dir, -step);
	}
}
