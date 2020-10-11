#include "../includes/wolf3d.h"

void    render_text(int fps, SDL_Surface *screen)
{
	TTF_Font*   my_font = NULL;

	my_font = TTF_OpenFont("ttf/19888.ttf", 12);
	if (my_font == NULL)
	{
		printf("error\n");
		exit(1);
	}
	SDL_Color fore_color = { RED_COLOR };
	SDL_Color back_color = { BLUE_COLOR };
	SDL_Surface* textSurface = NULL;
	textSurface = TTF_RenderText_Shaded(my_font, ft_itoa(fps), fore_color, back_color);
	if(textSurface == NULL)
	{
		printf("error\n");
		exit(1);
	}
	SDL_Rect textLocation = { W - 16, 2, 0, 0 };
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
	TTF_CloseFont(my_font); // вот думаю можно и не закрывать а потом ехит все равно 
}