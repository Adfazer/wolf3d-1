#include "../includes/wolf3d.h"

void    render_fps(int fps, SDL_Surface *screen, t_bonus *bon)
{
	if (bon->my_font == NULL)
	{
		printf("error\n");
		exit(1);
	}
	SDL_Color fore_color = { RED_COLOR };
	SDL_Color back_color = { BLUE_COLOR };
	SDL_Surface* textSurface = NULL;
	char *str;
	str = ft_itoa(fps);
	textSurface = TTF_RenderText_Shaded(bon->my_font, str, fore_color, back_color);
	free(str);
	if(textSurface == NULL)
	{
		printf("error\n");
		exit(1);
	}
	SDL_Rect textLocation = { W - 16, 2, 0, 0 };
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
	// TTF_CloseFont(my_font); // вот думаю можно и не закрывать а потом ехит все равно 
}