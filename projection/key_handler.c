/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 16:49:50 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/02 07:19:12 by mrakotos         ###   ########.fr       */
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

int key_handler(int key, t_test* data)
{
	printf("%d pressed.\n", key);
	if (key == 65307) close_window(data);
	if (key == 65364)
	{
		if (tmp_map[data->playerY + 1][data->playerX] != 1)
		{
			++data->playerY;
			draw(data);
		}
	}
	if (key == 65362)
	{
		if (tmp_map[data->playerY - 1][data->playerX] != 1)
		{
			--data->playerY;
			draw(data);
		}
		draw(data);
	}
	if (key == 65361)
	{
		if (tmp_map[data->playerY][data->playerX - 1] != 1)
		{
			--data->playerX;
			draw(data);
		}
		draw(data);
	}
	if (key == 65363)
	{
		if (tmp_map[data->playerY][data->playerX + 1] != 1)
		{
			++data->playerX;
			draw(data);
		}
		draw(data);
	}
	return (0);
}
