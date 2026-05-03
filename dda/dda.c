/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 09:27:35 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/03 16:06:46 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

t_point has_hit(t_point p, float dir)
{
	t_point tmp;
	t_point delta;
	t_point side;
	t_point angle;
	t_point step;
	t_point res;
	float t;
	int hit;
	int mapX;
	int mapY;

	hit = 0;
	mapX = (int)p.x;
	mapY = (int)p.y;
	tmp.x = p.x;
	tmp.y = p.y;
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
	while (hit == 0)
	{
		if (side.x < side.y)
		{
			t = side.x;
			side.x += delta.x;
			mapX += (int)step.x;
		}
		else
		{
			t = side.y;
			side.y += delta.y;
			mapY += (int)step.y;
		}
		if (tmp_map[mapY][mapX] == 1) hit = 1;
	}
	res.x = p.x + t * angle.x;
	res.y = p.y + t * angle.y;
	return (res);
}