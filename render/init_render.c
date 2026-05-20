/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:40:34 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/20 06:42:41 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	init_move(t_test *data)
{
	data->last_frame = get_time();
	data->move.rotate_right = 0;
	data->move.rotate_left = 0;
	data->move.forward = 0;
	data->move.backward = 0;
	data->move.left = 0;
	data->move.right = 0;
}

static int	init_mlx_data(t_test *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	data->windows_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, WIN_TITLE);
	if (!data->windows_ptr)
		return (0);
	data->img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length,
			&data->endian);
	return (1);
}

static void	init_player_data(t_test *data, t_data *parse)
{
	int	x;
	int	y;

	x = (int)data->px;
	y = (int)data->py;
	data->px = parse->pos[0] + 0.5;
	data->py = parse->pos[1] + 0.5;
	data->direction = set_player_direction(data->map[y][x]);
	data->player_box = 0.2;
	data->fov = 1.15;
	data->fov_max = data->direction + (data->fov / 2);
	data->fov_min = data->direction - (data->fov / 2);
	data->step = 0.001;
}

static void	init_map(t_test *data, t_data *parse)
{
	data->map = parse->map_tab;
	data->ceil_color = parse->colors[0];
	data->floor_color = parse->colors[1];
	data->map_size_x = parse->end_w;
	data->map_size_y = parse->map_height;
}

int	init_render(t_test *data, t_data *parse)
{
	if (!init_mlx_data(data))
		return (0);
	init_map(data, parse);
	init_player_data(data, parse);
	init_move(data);
	init_textures(parse, data);
	return (1);
}
