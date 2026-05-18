/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:03:39 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/18 17:41:45 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
	t_params	d;
	int			len;
	t_point		p;

	p.x = data->px;
	p.y = data->py;
	d = dda(p, dir, data);
	d.d = d.d * cos(dir - data->direction);
	len = (int)(WIN_H / d.d);
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

void	render(t_test *data)
{
	int		x;
	float	step;
	float	angle;

	x = 0;
	step = data->fov / WIN_W;
	data->fov_min = data->direction - (data->fov / 2);
	data->fov_max = data->direction + (data->fov / 2);
	angle = data->fov_min;
	reset_img(data);
	while (x < WIN_W)
	{
		render_column(angle, x, data);
		angle += step;
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->windows_ptr, data->img, 0, 0);
}
