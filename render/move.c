/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 18:59:59 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/20 06:52:56 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	move_forward(t_test *data)
{
	t_point	next;

	next.x = data->px + cos(data->direction) * MOVE_SPEED * data->game_time;
	next.y = data->py + sin(data->direction) * MOVE_SPEED * data->game_time;
	if (is_move_valid(data, next.x, data->py))
		data->px = next.x;
	if (is_move_valid(data, data->px, next.y))
		data->py = next.y;
}

static void	move_backward(t_test *data)
{
	t_point	next;
	double	game_time;

	game_time = data->game_time;

	next.x = data->px - cos(data->direction) * MOVE_SPEED * data->game_time;
	next.y = data->py - sin(data->direction) * MOVE_SPEED * data->game_time;
	if (is_move_valid(data, next.x, data->py))
		data->px = next.x;
	if (is_move_valid(data, data->px, next.y))
		data->py = next.y;
}

static void	move_left(t_test *data)
{
	t_point	next;

	next.x = data->px + sin(data->direction) * MOVE_SPEED * data->game_time;
	next.y = data->py - cos(data->direction) * MOVE_SPEED * data->game_time;
	if (is_move_valid(data, next.x, data->py))
		data->px = next.x;
	if (is_move_valid(data, data->px, next.y))
		data->py = next.y;
}

static void	move_right(t_test *data)
{
	t_point	next;

	next.x = data->px - sin(data->direction) * MOVE_SPEED * data->game_time;
	next.y = data->py + cos(data->direction) * MOVE_SPEED * data->game_time;
	if (is_move_valid(data, next.x, data->py))
		data->px = next.x;
	if (is_move_valid(data, data->px, next.y))
		data->py = next.y;
}

int	move(t_test *data)
{
	update_game_time(data);
	if (data->move.forward)
		move_forward(data);
	if (data->move.backward)
		move_backward(data);
	if (data->move.left)
		move_left(data);
	if (data->move.right)
		move_right(data);
	if (data->move.rotate_left)
		data->direction -= ROTATION_SPEED * data->game_time;
	normalize_direction(data);
	if (data->move.rotate_right)
		data->direction += ROTATION_SPEED * data->game_time;
	normalize_direction(data);
	render(data);
	return (0);
}
