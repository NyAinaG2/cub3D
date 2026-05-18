/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 09:27:35 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/18 17:43:38 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"
#include <math.h>

static void	set_dda_params(t_vec *vec, t_point p, float dir)
{
	vec->hit = 0;
	vec->first_hit = 'x';
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

static void	dda_loop(t_vec *vec, t_test *data)
{
	while (vec->hit == 0)
	{
		if (vec->side.x < vec->side.y)
		{
			vec->t = vec->side.x;
			vec->first_hit = 'x';
			vec->side.x += vec->delta.x;
			vec->map_x += (int)(vec->step.x);
		}
		else
		{
			vec->t = vec->side.y;
			vec->first_hit = 'y';
			vec->side.y += vec->delta.y;
			vec->map_y += (int)(vec->step.y);
		}
		if (data->map[vec->map_y][vec->map_x] == '1')
			vec->hit = 1;
	}
}

static void	get_dda_result(t_params *res, t_vec *vec)
{
	double	tmp;

	if (vec->first_hit == 'x')
		res->x = modf(vec->map_y, &tmp);
	else
		res->x = modf(vec->map_x, &tmp);
	res->d = vec->t;
	res->side = vec->first_hit;
}

t_params	dda(t_point p, float dir, t_test *data)
{
	t_vec		vec;
	t_params	res;

	set_dda_params(&vec, p, dir);
	dda_loop(&vec, data);
	get_dda_result(&res, &vec);
	return (res);
}
