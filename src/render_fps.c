#include "../includes/wolf3d.h"

void    render_fps(t_wolf *wolf, t_bonus *bon)
{
	if (!bon->startTime)
	{
		bon->startTime = SDL_GetTicks();
	}
	if (bon->startTime + 1000 < SDL_GetTicks())
	{
		bon->startTime = SDL_GetTicks();
		bon->fps = bon->fps_count;
		bon->fps_count = 0;
	}
	bon->fps_count++;
	if (!bon->fps)
		return ;
	if (bon->my_font == NULL)
	{
		printf("error\n");
		exit(1);
	}
	SDL_Color fore_color = { COLOR_RED };
	SDL_Color back_color = { COLOR_BLUE };
	SDL_Surface* textSurface = NULL;
	char *str;
	str = ft_itoa(bon->fps);
	textSurface = TTF_RenderText_Shaded(bon->my_font, str, fore_color, back_color);
	free(str);
	if(textSurface == NULL)
	{
		printf("error\n");
		exit(1);
	}
	SDL_Rect textLocation = { W - 32, 2, 0, 0 };
	SDL_BlitSurface(textSurface, NULL, wolf->surface, &textLocation);
	// TTF_CloseFont(my_font); // вот думаю можно и не закрывать а потом ехит все равно 
}