/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:27:09 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 18:29:01 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint32	*target_pixel;

	target_pixel = (Uint32 *)((Uint8 *)surface->pixels + y \
	* surface->pitch + x * sizeof(*target_pixel));
	*target_pixel = pixel;
}

Uint32		getpixel(SDL_Surface *surface, int x, int y)
{
	Uint8	*p;

	p = (Uint8 *)surface->pixels + y * surface->pitch + x \
	* surface->format->BytesPerPixel;
	return (*(Uint32 *)p);
}
