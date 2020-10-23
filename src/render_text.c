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

SDL_Color	set_color_sdl(int a, int b, int c)
{
	SDL_Color	color;

	color.r = a;
	color.g = b;
	color.b = c;
	color.a = 255;
	return (color);
}

SDL_Rect	set_rect_sdl(int x, int y, int w, int h)
{
	SDL_Rect	location;

	location.w = w;
	location.h = h;
	location.x = x;
	location.y = y;
	return (location);
}

int			get_fps_time(t_bonus *bon)
{
	if (!bon->fps)
		return (1);
	if (!bon->startTime)
		bon->startTime = SDL_GetTicks();
	if (bon->startTime + 1000 < SDL_GetTicks())
	{
		bon->startTime = SDL_GetTicks();
		bon->fps = bon->fps_count;
		bon->fps_count = 0;
	}
	return (0);
}

void		render_text(t_wolf *wolf, char *text, SDL_Rect location, SDL_Color f_b_color[2])
{
	SDL_Surface		*txt_sur;

	txt_sur = TTF_RenderText_Shaded(wolf->bon->my_font, text,
	f_b_color[TEXT_FOREGROUND_COLOR], f_b_color[TEXT_BACKGROUND_COLOR]);
	free(text);
	if (txt_sur == NULL)
		error(wolf, SDL_GetError());
	SDL_BlitSurface(txt_sur, NULL, wolf->surface, &location);
	SDL_FreeSurface(txt_sur);
}

void		render_fps(t_wolf *wolf, t_bonus *bon)
{
	SDL_Color		f_b_color[2];
	SDL_Surface		*txt_sur;
	char			*str1;
	char			*str2;

	if (get_fps_time(bon))
		return ;
	f_b_color[TEXT_FOREGROUND_COLOR] = set_color_sdl(COLOR_RED);
	f_b_color[TEXT_BACKGROUND_COLOR] = set_color_sdl(COLOR_BLUE);
	txt_sur = NULL;
	bon->fps_count++;
	str1 = ft_itoa(bon->fps);
	str2 = ft_strjoin("FPS: ", str1);
	free(str1);
	render_text(wolf, str2,
		set_rect_sdl(W - (int)(H / 10) * 2, 2, 0, 0), f_b_color);
}

void		render_score_coin(t_wolf *wolf)
{
	SDL_Color		f_b_color[2];
	SDL_Surface		*text_surface;
	SDL_Rect		text_location;
	char			*str;
	char			str_tmp[50];

	f_b_color[0] = set_color_sdl(COLOR_RED);
	f_b_color[1] = set_color_sdl(COLOR_BLUE);
	text_surface = NULL;
	text_location = set_rect_sdl(W - (int)(H / 28) * 9,
		H - (int)(H / 28), 0, 0);
	ft_strcpy(str_tmp, "score coin: ");
	str = ft_itoa(wolf->bon->score_coin);
	ft_strcat(str_tmp, str);
	text_surface = TTF_RenderText_Shaded(wolf->bon->my_font, str_tmp,
		f_b_color[0], f_b_color[1]);
	free(str);
	if (text_surface == NULL)
		error(wolf, SDL_GetError());
	SDL_BlitSurface(text_surface, NULL, wolf->surface, &text_location);
	SDL_FreeSurface(text_surface);
}
