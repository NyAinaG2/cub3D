/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:03:39 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/01 10:21:04 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projection.h"

void put_pixel_to_img(t_test* data, int x, int y, int color)
{
	char* addr;

	if (x < 0 || x >= WIN_W) return;
	if (y < 0 || y >= WIN_H) return;

	addr = data->addr + ((y * data->line_length) + (x * (data->bpp / 8)));
	*(unsigned int*)addr = color;
}

int init(t_test* data_ptr)
{
	data_ptr->mlx_ptr = mlx_init();
	if (!data_ptr->mlx_ptr) return (0);
	data_ptr->windows_ptr =
		mlx_new_window(data_ptr->mlx_ptr, WIN_W, WIN_H, WIN_TITLE);
	if (!data_ptr->windows_ptr) return (0);
	data_ptr->img = mlx_new_image(data_ptr->mlx_ptr, WIN_W, WIN_H);
	data_ptr->addr = mlx_get_data_addr(data_ptr->img,
									   &data_ptr->bpp,
									   &data_ptr->line_length,
									   &data_ptr->endian);
	data_ptr->mapSizeX = 12;
	data_ptr->mapSizeY = 12;
	data_ptr->playerX = 3;
	data_ptr->playerY = 5;
	data_ptr->mapSizeY = 12;
	data_ptr->offsetX = 32;
	data_ptr->offsetY = 32;
	return (1);
}

void draw(t_test* data)
{
	unsigned int i;
	unsigned int j;
	int x;
	int y;

	i = 0;
	j = 0;
	while (i < 6)
	{
		while (j < 7)
		{
			x = 0;
			while (x < 64)
			{
				y = 0;
				while (y < 64)
				{
					if (tmp_map[j][i] == 1)
						put_pixel_to_img(
							data, j * 64 + x, i * 64 + y, 0x08F0F4);
					y++;
				}
				x++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->windows_ptr, data->img, 0, 0);
}