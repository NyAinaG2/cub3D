/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:03:39 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/02 09:36:26 by mrakotos         ###   ########.fr       */
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

void draw_rectangle(t_test* data, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < data->tile_size)
	{
		j = 0;
		while (j < data->tile_size)
		{
			put_pixel_to_img(
				data, x * data->tile_size + i, y * data->tile_size + j, color);
			j++;
		}
		i++;
	}
}

void draw_player(t_test* data)
{
	int i;
	int j;
	int size;

	i = 0;
	size = (data->tile_size / 5);
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_to_img(data,
							 data->playerX * data->tile_size + i,
							 data->playerY * data->tile_size + j,
							 0x555555);
			j++;
		}
		i++;
	}
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
	data_ptr->mapSizeX = 6;
	data_ptr->mapSizeY = 7;
	data_ptr->playerX = 3;
	data_ptr->playerY = 5;
	data_ptr->offsetX = 32;
	data_ptr->offsetY = 32;
	data_ptr->tile_size = 64;
	return (1);
}

void draw(t_test* data)
{
	int x;
	int y;

	x = 0;
	while (x < data->mapSizeX)
	{
		y = 0;
		while (y < data->mapSizeY)
		{
			if (tmp_map[y][x] == 1)
				draw_rectangle(data, x, y, 0x569874);
			else
				draw_rectangle(data, x, y, 0);
			y++;
		}
		x++;
	}
	draw_player(data);
	mlx_put_image_to_window(data->mlx_ptr, data->windows_ptr, data->img, 0, 0);
	printf("Drawing!\n");
}