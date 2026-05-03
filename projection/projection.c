/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:03:39 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/03 11:24:01 by mrakotos         ###   ########.fr       */
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

void draw_line_dda(t_test* data, t_point p0, t_point p1, int color)
{
	t_point delta;
	t_point inc;
	float steps;
	int i;

	delta.x = p1.x - p0.x;
	delta.y = p1.y - p0.y;
	if (fabs(delta.x) > fabs(delta.y))
		steps = fabs(delta.x);
	else
		steps = fabs(delta.y);
	inc.x = delta.x / steps;
	inc.y = delta.y / steps;
	i = 0;
	while (i <= (int)steps)
	{
		put_pixel_to_img(data, (int)p0.x, (int)p0.y, color);
		p0.x += inc.x;
		p0.y += inc.y;
		i++;
	}
}

void set_center(t_test* data, t_point* c)
{
	c->x = data->playerX * data->tile_size;
	c->y = data->playerY * data->tile_size;
}

void draw_player(t_test* data)
{
	t_point p0;
	t_point p1;
	t_point p2;
	t_point c;

	set_center(data, &c);
	p0.x = c.x + data->playerR * cos(data->direction);
	p0.y = c.y + data->playerR * sin(data->direction);
	p1.x = c.x + data->playerR * cos(data->direction + 2.44);
	p1.y = c.y + data->playerR * sin(data->direction + 2.44);
	p2.x = c.x + data->playerR * cos(data->direction + 3.84);
	p2.y = c.y + data->playerR * sin(data->direction + 3.84);
	draw_line_dda(data, p0, p1, 0xFFFFFF);
	draw_line_dda(data, p0, p2, 0xFFFFFF);
	draw_line_dda(data, p1, p2, 0xFFFFFF);
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
	data_ptr->playerR = 10;
	data_ptr->direction = 0;
	data_ptr->offsetX = 32;
	data_ptr->offsetY = 32;
	data_ptr->tile_size = 64;
	return (1);
}

void draw_ray(t_test* data)
{
	t_point p0;
	t_point p1;

	p0.x = data->playerX * data->tile_size;
	p0.y = data->playerY * data->tile_size;
	p1 = has_hit(p0, data->direction);
	p1.x = p1.x * data->tile_size;
	p1.y = p1.y * data->tile_size;
	draw_line_dda(data, p0, p1, 0x555555);
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
	draw_ray(data);
	mlx_put_image_to_window(data->mlx_ptr, data->windows_ptr, data->img, 0, 0);
}