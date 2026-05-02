/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 16:49:50 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/02 11:19:42 by mrakotos         ###   ########.fr       */
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

int key_handler(int key, t_test* data)
{
	printf("%d pressed.\n", key);
	if (key == 65307) close_window(data);
	if (key == 65362)
	{
		data->playerY += cos(data->direction) * MOVE_SPEED;
		data->playerX += sin(data->direction) * MOVE_SPEED;
		draw(data);
	}
	if (key == 65364)
	{
		if (tmp_map[(int)(data->playerY - 0.3)][(int)data->playerX] != 1)
			data->playerY -= 0.2;
		else
			data->playerY = floorf(data->playerY);
		draw(data);
	}
	if (key == 65361)
	{
		data->direction -= 0.2;
		draw(data);
	}
	if (key == 65363)
	{
		if (data->direction) data->direction += 0.2;
		draw(data);
	}
	return (0);
}
