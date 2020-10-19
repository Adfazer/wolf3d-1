/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:26:06 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 18:26:22 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	add_arc(float *arc, float to_add)
{
	*arc += to_add;
	if (*arc < 0)
		*arc += RAD_360;
	else if (*arc >= RAD_360)
		*arc -= RAD_360;
	return (1);
}

int	add_floor_offset(int *offset, int to_add)
{
	*offset += to_add;
	if (*offset < 0)
		*offset += CUBE;
	else if (*offset >= CUBE)
		*offset -= CUBE;
	return (1);
}

int	max(int a, int b)
{
	return (a > b ? a : b);
}

int	is_angle(float angle, float rad)
{
	return (fabsf(cosf(angle) - cosf(rad)) < KLUDGE);
}

int	float_is_equal(float a, float b)
{
	return (fabsf(a - b) < KLUDGE);
}
