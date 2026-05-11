/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 09:27:35 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/11 19:44:10 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

static void	set_dda_params(t_vec *vec, t_point p, float dir)
{
	vec->hit = 0;
	vec->map_x = (int)p.x;
	vec->map_y = (int)p.y;
	vec->angle.x = cos(dir);
	vec->angle.y = sin(dir);
	vec->step.x = copysign(1.0, vec->angle.x);
	vec->step.y = copysign(1.0, vec->angle.y);
	vec->delta.x = fabs(1 / vec->angle.x);
	vec->delta.y = fabs(1 / vec->angle.y);
	if (vec->step.x > 0)
		vec->side.x = (floor(p.x + 1) - p.x) * vec->delta.x;
	else
		vec->side.x = (p.x - floor(p.x)) * vec->delta.x;
	if (vec->step.y > 0)
		vec->side.y = (floor(p.y + 1) - p.y) * vec->delta.y;
	else
		vec->side.y = (p.y - floor(p.y)) * vec->delta.y;
}

static void	dda_loop(t_vec *vec)
{
	while (vec->hit == 0)
	{
		if (vec->side.x < vec->side.y)
		{
			vec->t = vec->side.x;
			vec->side.x += vec->delta.x;
			vec->map_x += (int)(vec->step.x);
		}
		else
		{
			vec->t = vec->side.y;
			vec->side.y += vec->delta.y;
			vec->map_y += (int)(vec->step.y);
		}
		if (tmp_map[vec->map_y][vec->map_x] == 1)
			vec->hit = 1;
	}
}

float	dda(t_point p, float dir)
{
	t_vec	vec;

	set_dda_params(&vec, p, dir);
	dda_loop(&vec);
	return (vec.t);
}
