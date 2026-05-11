/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 16:49:50 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/11 19:34:15 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projection.h"

int	close_window(t_test *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img);
	mlx_destroy_window(data->mlx_ptr, data->windows_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}

void	normalize_direction(t_test *data)
{
	if (data->direction > 3.14)
	{
		data->direction -= 6.28;
		return ;
	}
	if (data->direction <= -3.14)
		data->direction += 6.28;
}

int	key_press(int key, t_test *data)
{
	if (key == 65307)
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

int	key_release(int key, t_test *data)
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

int	move(t_test *data)
{
	if (data->move.forward)
		move_forward(data);
	if (data->move.backward)
		move_backward(data);
	if (data->move.left)
		move_left(data);
	if (data->move.right)
		move_right(data);
	if (data->move.rotate_left)
		data->direction -= ROTATION_SPEED;
	normalize_direction(data);
	if (data->move.rotate_right)
		data->direction += ROTATION_SPEED;
	normalize_direction(data);
	draw(data);
	return (0);
}
