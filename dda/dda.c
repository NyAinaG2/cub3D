/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 09:27:35 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/03 15:23:32 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

t_point has_hit(t_point p, float dir)

{
	t_point delta;
	t_point side;
	t_point angle;
	t_point step;
	t_point res;
	float t;

	angle.x = cos(dir);
	angle.y = sin(dir);
	step.x = copysign(1.0, angle.x);
	step.y = copysign(1.0, angle.y);
	delta.x = fabs(1 / angle.x);
	delta.y = fabs(1 / angle.y);
	if (step.x > 0)
		side.x = (floor(p.x + 1) - p.x) * delta.x;
	else
		side.x = (p.x - floor(p.x)) * delta.x;
	if (step.y > 0)
		side.y = (floor(p.y + 1) - p.y) * delta.y;
	else
		side.y = (p.y - floor(p.y)) * delta.y;
	if (side.x > side.y)
		t = side.y;
	else
		t = side.x;
	res.x = p.x + t * angle.x;
	res.y = p.y + t * angle.y;
	return (res);
}