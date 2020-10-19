/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:59 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 19:43:59 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	SDL_Color fore_color = { COLOR_RED };
	SDL_Color back_color = { COLOR_BLUE };
	SDL_Surface* textSurface = NULL;
	char *str;
	str = ft_itoa(bon->fps);
	textSurface = TTF_RenderText_Shaded(bon->my_font, str, fore_color, back_color);
	free(str);
	if(textSurface == NULL)
		error(wolf, SDL_GetError());
	SDL_Rect textLocation = { W - (int)(H / 28) * 2, 2, 0, 0 };
	SDL_BlitSurface(textSurface, NULL, wolf->surface, &textLocation);
	SDL_FreeSurface(textSurface);
}

void    render_score_coin(t_wolf *wolf)
{
	SDL_Color fore_color = { COLOR_RED };
	SDL_Color back_color = { COLOR_BLUE };
	SDL_Surface* text_surface = NULL;
	SDL_Rect text_location = { W - (int)(H / 28) * 9, H - (int)(H / 28), 0, 0 };
	char *str;
	char str_tmp[50];
	ft_strcpy(str_tmp, "score coin: ");
	str = ft_itoa(wolf->bon->score_coin);
	ft_strcat(str_tmp, str);
	text_surface = TTF_RenderText_Shaded(wolf->bon->my_font, str_tmp, fore_color, back_color);
	free(str);
	if(text_surface == NULL)
		error(wolf, SDL_GetError());
	SDL_BlitSurface(text_surface, NULL, wolf->surface, &text_location);
	SDL_FreeSurface(text_surface);
}
