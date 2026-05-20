/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:03:39 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/20 11:38:49 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	render_column(float dir, int x, t_game *data)
{
	t_params	d;
	int			len;
	t_point		p;

	p.x = data->px;
	p.y = data->py;
	d = dda(p, dir, data);
	len = (int)lroundf((float)WIN_H / d.d);
	draw_column(len, x, data, &d);
}

void	reset_img(t_game *data)
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

void	render(t_game *data)
{
	int		x;
	float	angle;
	float	camera_x;

	x = 0;
	camera_x = 0;
	data->fov_min = data->direction - (data->fov / 2);
	data->fov_max = data->direction + (data->fov / 2);
	angle = data->fov_min;
	reset_img(data);
	while (x < WIN_W)
	{
		camera_x = 2.0f * x / (float)WIN_W - 1.0f;
		angle = data->direction + atan(camera_x * tan(data->fov / 2.0f));
		render_column(angle, x, data);
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->windows_ptr, data->img, 0, 0);
}
