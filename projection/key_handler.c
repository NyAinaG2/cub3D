/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 16:49:50 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/11 11:03:43 by mrakotos         ###   ########.fr       */
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
		data->direction -= PI2;
		return ;
	}
	if (data->direction <= -3.14)
		data->direction += PI2;
}

int	is_move_valid(t_point c, t_point next)
{
	if (tmp_map[(int)next.y][(int)c.x] == 1)
		return (0);
	if (tmp_map[(int)c.y][(int)next.x] == 1)
		return (0);
	return (1);
}

int	collisionF(t_test *data)
{
	t_point	c;
	t_point	next;
	float	direction;

	direction = copysign(1.0, cos(data->direction));
	c.y = data->playerY + sin(data->direction) * MOVE_SPEED;
	c.x = data->playerX + cos(data->direction) * MOVE_SPEED;
	next.x = c.x + MOVE_SPEED * direction;
	direction = copysign(1.0, sin(data->direction));
	next.y = c.y + MOVE_SPEED * direction;
	if (is_move_valid(c, next))
		return (0);
	return (1);
}

int	collisionB(t_test *data)
{
	t_point	c;
	t_point	next;
	float	direction;

	direction = copysign(1.0, cos(data->direction));
	c.y = data->playerY - sin(data->direction) * MOVE_SPEED;
	c.x = data->playerX - cos(data->direction) * MOVE_SPEED;
	next.x = c.x - MOVE_SPEED * direction;
	direction = copysign(1.0, sin(data->direction));
	next.y = c.y - MOVE_SPEED * direction;
	if (is_move_valid(c, next))
		return (0);
	return (1);
}

int	key_press(int key, t_test *data)
{
	if (key == 65307)
		close_window(data);
	if (key == 65362)
		data->move.forward = 1;
	if (key == 65364)
		data->move.backward = 1;
	if (key == 65361)
		data->move.rotate_left = 1;
	if (key == 65363)
		data->move.rotate_right = 1;
	return (0);
}

int	key_release(int key, t_test *data)
{
	if (key == 65362)
		data->move.forward = 0;
	if (key == 65364)
		data->move.backward = 0;
	if (key == 65361)
		data->move.rotate_left = 0;
	if (key == 65363)
		data->move.rotate_right = 0;
	return (0);
}

int	move(t_test *data)
{
	if (data->move.forward)
	{
		if (!collisionF(data))
		{
			data->playerY += sin(data->direction) * MOVE_SPEED;
			data->playerX += cos(data->direction) * MOVE_SPEED;
		}
	}
	if (data->move.backward)
	{
		if (!collisionB(data))
		{
			data->playerY -= sin(data->direction) * MOVE_SPEED;
			data->playerX -= cos(data->direction) * MOVE_SPEED;
		}
	}
	if (data->move.rotate_left)
		data->direction -= ROTATION_SPEED;
	if (data->move.rotate_right)
		data->direction += ROTATION_SPEED;
	normalize_direction(data);
	draw(data);
	return (0);
}
