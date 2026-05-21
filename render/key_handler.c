/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 16:49:50 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/21 12:08:49 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	normalize_direction(t_game *data)
{
	if (data->direction > 3.14)
	{
		data->direction -= 6.28;
		return ;
	}
	if (data->direction <= -3.14)
		data->direction += 6.28;
}

int	key_press(int key, t_game *data)
{
	if (key == ESC)
		close_window(data);
	if (key == KEY_W)
		data->move.forward = 1;
	if (key == KEY_S)
		data->move.backward = 1;
	if (key == KEY_A)
		data->move.left = 1;
	if (key == KEY_D)
		data->move.right = 1;
	if (key == KEY_LEFT)
		data->move.rotate_left = 1;
	if (key == KEY_RIGHT)
		data->move.rotate_right = 1;
	return (0);
}

int	key_release(int key, t_game *data)
{
	if (key == KEY_W)
		data->move.forward = 0;
	if (key == KEY_S)
		data->move.backward = 0;
	if (key == KEY_A)
		data->move.left = 0;
	if (key == KEY_D)
		data->move.right = 0;
	if (key == KEY_LEFT)
		data->move.rotate_left = 0;
	if (key == KEY_RIGHT)
		data->move.rotate_right = 0;
	return (0);
}

int	focus_out(t_game *data)
{
	data->move.backward = 0;
	data->move.forward = 0;
	data->move.left = 0;
	data->move.right = 0;
	data->move.rotate_left = 0;
	data->move.rotate_right = 0;
	return (0);
}
