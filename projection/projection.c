/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:03:39 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/07 09:06:09 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projection.h"

void	put_pixel_to_img(t_test *data, int x, int y, int color)
{
	char	*addr;

	if (x < 0 || x >= WIN_W)
		return ;
	if (y < 0 || y >= WIN_H)
		return ;
	addr = data->addr + ((y * data->line_length) + (x * (data->bpp / 8)));
	*(unsigned int *)addr = color;
}

int	init(t_test *data_ptr)
{
	data_ptr->mlx_ptr = mlx_init();
	if (!data_ptr->mlx_ptr)
		return (0);
	data_ptr->windows_ptr = mlx_new_window(data_ptr->mlx_ptr, WIN_W, WIN_H,
			WIN_TITLE);
	if (!data_ptr->windows_ptr)
		return (0);
	data_ptr->img = mlx_new_image(data_ptr->mlx_ptr, WIN_W, WIN_H);
	data_ptr->addr = mlx_get_data_addr(data_ptr->img, &data_ptr->bpp,
			&data_ptr->line_length, &data_ptr->endian);
	data_ptr->mapSizeX = 6;
	data_ptr->mapSizeY = 7;
	data_ptr->playerX = 3;
	data_ptr->playerY = 5;
	data_ptr->playerR = 10;
	data_ptr->direction = 2;
	data_ptr->fov = 1.15;
	data_ptr->fovMax = data_ptr->direction + (data_ptr->fov / 2);
	data_ptr->fovMin = data_ptr->direction - (data_ptr->fov / 2);
	data_ptr->step = 0.001;
	data_ptr->wall_color = 0x707070;
	data_ptr->ceil_color = 0x383838;
	data_ptr->floor_color = 0x525252;
	data_ptr->tile_size = 64;
	return (1);
}

void	draw_column(int len, int x, t_test *data)
{
	int	start;
	int	end;

	start = -len / 2 + WIN_H / 2;
	end = len / 2 + WIN_H / 2;
	if (start < 0)
		start = 0;
	if (start >= WIN_H)
		end = WIN_H - 1;
	while (start < end)
	{
		put_pixel_to_img(data, x, start, data->wall_color);
		start++;
	}
}

void	render_column(float dir, int x, t_test *data)
{
	float	d;
	int		len;
	t_point	p;

	p.x = data->playerX;
	p.y = data->playerY;
	d = dda(p, dir);
	d = d * cos(dir - data->direction);
	len = (int)(WIN_H / d);
	draw_column(len, x, data);
}

void	reset_img(t_test *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_W)
	{
		y = 0;
		while (y < WIN_H)
		{
			if (y > WIN_H / 2)
				put_pixel_to_img(data, x, y, data->ceil_color);
			else
				put_pixel_to_img(data, x, y, data->floor_color);
			y++;
		}
		x++;
	}
}

void	draw(t_test *data)
{
	int		x;
	float	step;
	float	angle;

	x = 0;
	step = data->fov / WIN_W;
	data->fovMin = data->direction - (data->fov / 2);
	data->fovMax = data->direction + (data->fov / 2);
	angle = data->fovMin;
	reset_img(data);
	while (x < WIN_W)
	{
		render_column(angle, x, data);
		angle += step;
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->windows_ptr, data->img, 0, 0);
}
