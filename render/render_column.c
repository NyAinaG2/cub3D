/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_column.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:45:01 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/19 17:48:03 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	get_texture_color(t_texture *texture, t_column *column)
{
	int	y;
	int	res;

	y = get_texture_y(texture, column);
	res = sample_texture(texture, column->x_texture_img, y);
	return (res);
}

void	draw_column(int len, int x, t_test *data, t_params *params)
{
	int			start;
	int			end;
	int			y;
	t_column	column;
	t_texture	*texture;

	texture = get_texture(params, data);
	column.len = len;
	column.start = (WIN_H - len) / 2;
	start = column.start;
	end = column.start + len;
	column.x_texture_img = get_texture_x(texture, params);
	column.y_pos = 0.0f;
	column.y_step = (float)texture->size_y / (float)column.len;
	if (start < 0)
	{
		column.y_pos = (float)(-start) * column.y_step;
		start = 0;
	}
	if (end > WIN_H)
		end = WIN_H;
	y = start;
	while (y < end)
	{
		column.current = y;
		put_pixel_to_img(data, x, y, get_texture_color(texture, &column));
		column.y_pos += column.y_step;
		y++;
	}
}
