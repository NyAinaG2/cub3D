/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 18:59:59 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/11 19:30:05 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projection.h"

void	move_forward(t_test *data)
{
	t_point	next;

	next.x = data->px + cos(data->direction) * MOVE_SPEED;
	next.y = data->py + sin(data->direction) * MOVE_SPEED;
	if (is_move_valid(data, next.x, data->py))
		data->px = next.x;
	if (is_move_valid(data, data->px, next.y))
		data->py = next.y;
}

void	move_backward(t_test *data)
{
	t_point	next;

	next.x = data->px - cos(data->direction) * MOVE_SPEED;
	next.y = data->py - sin(data->direction) * MOVE_SPEED;
	if (is_move_valid(data, next.x, data->py))
		data->px = next.x;
	if (is_move_valid(data, data->px, next.y))
		data->py = next.y;
}

void	move_left(t_test *data)
{
	t_point	next;

	next.x = data->px + sin(data->direction) * MOVE_SPEED;
	next.y = data->py - cos(data->direction) * MOVE_SPEED;
	if (is_move_valid(data, next.x, data->py))
		data->px = next.x;
	if (is_move_valid(data, data->px, next.y))
		data->py = next.y;
}

void	move_right(t_test *data)
{
	t_point	next;

	next.x = data->px - sin(data->direction) * MOVE_SPEED;
	next.y = data->py + cos(data->direction) * MOVE_SPEED;
	if (is_move_valid(data, next.x, data->py))
		data->px = next.x;
	if (is_move_valid(data, data->px, next.y))
		data->py = next.y;
}
