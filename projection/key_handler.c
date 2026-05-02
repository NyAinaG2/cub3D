/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 16:49:50 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/02 18:05:58 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projection.h"

int close_window(t_test* data)
{
	mlx_destroy_image(data->mlx_ptr, data->img);
	mlx_destroy_window(data->mlx_ptr, data->windows_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}

void normalize_direction(t_test* data)
{
	if (data->direction > 3.14)
	{
		data->direction -= PI2;
		return;
	}
	if (data->direction <= -3.14) data->direction += PI2;
}

int collisionX(t_test* data)
{
	t_point next;

	next.x = data->playerX + cos(data->direction) * MOVE_SPEED;
	next.x = next.x + MOVE_SPEED;
	next.y = data->playerY;
	if (tmp_map[(int)next.y][(int)next.x] == 1) return (1);
	return 0;
}

int collisionY(t_test* data)
{
	t_point next;

	next.x = data->playerX;
	next.y = data->playerY + sin(data->direction) * MOVE_SPEED * 2.1;
	if (tmp_map[(int)next.y][(int)next.x] == 1) return (1);
	return 0;
}

int key_handler(int key, t_test* data)
{
	printf("%d pressed.\n", key);
	if (key == 65307) close_window(data);
	if (key == 65362)
	{
		if (collisionX(data)) return (0);
		if (collisionY(data)) return (0);
		data->playerY += sin(data->direction) * MOVE_SPEED;
		data->playerX += cos(data->direction) * MOVE_SPEED;
		draw(data);
	}
	if (key == 65364)
	{
		if (collisionX(data)) return (0);
		if (collisionY(data)) return (0);
		data->playerY -= sin(data->direction) * MOVE_SPEED;
		data->playerX -= cos(data->direction) * MOVE_SPEED;
		draw(data);
	}
	if (key == 65361)
	{
		data->direction -= 0.2;
		normalize_direction(data);
		draw(data);
	}
	if (key == 65363)
	{
		data->direction += 0.2;
		normalize_direction(data);
		draw(data);
	}
	return (0);
}
