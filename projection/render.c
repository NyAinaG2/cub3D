/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:03:39 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/11 19:38:11 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projection.h"

void	init_move(t_test *data)
{
	data->move.rotate_right = 0;
	data->move.rotate_left = 0;
	data->move.forward = 0;
	data->move.backward = 0;
	data->move.left = 0;
	data->move.right = 0;
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
	data_ptr->map_size_x = 6;
	data_ptr->map_size_y = 7;
	data_ptr->px = 3;
	data_ptr->py = 5;
	data_ptr->player_box = 0.2;
	data_ptr->direction = 2;
	data_ptr->fov = 1.15;
	data_ptr->fov_max = data_ptr->direction + (data_ptr->fov / 2);
	data_ptr->fov_min = data_ptr->direction - (data_ptr->fov / 2);
	data_ptr->step = 0.001;
	data_ptr->wall_color = 0x707070;
	data_ptr->ceil_color = 0x383838;
	data_ptr->floor_color = 0x525252;
	data_ptr->tile_size = 64;
	data_ptr->game_time = get_current_time();
	init_move(data_ptr);
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

	p.x = data->px;
	p.y = data->py;
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
