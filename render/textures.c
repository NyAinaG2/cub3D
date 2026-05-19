/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:37:13 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/19 17:22:14 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int	sample_texture(t_texture *texture, int x, int y)
{
	char	*addr;

	if (x < 0 || x >= texture->size_x)
		return (0);
	if (y < 0 || y >= texture->size_y)
		return (0);
	addr = texture->addr + ((y * texture->line_length) + (x * (texture->bpp
					/ 8)));
	return (*(unsigned int *)addr);
}

static int	get_texture_y(t_texture *texture, t_column *column)
{
	int	res;

	if (column->len <= 0)
		return (0);
	res = (int)(column->y_pos * texture->size_y);
	if (res < 0)
		res = 0;
	if (res >= texture->size_y)
		res = texture->size_y - 1;
	return (res);
}

static int	get_texture_x(t_texture *texture, t_params *params)
{
	int		res;
	float	current_scale;

	current_scale = params->scale;
	if ((params->direction == 1 && params->side == 'y') || (params->direction ==
			-1 && params->side == 'x'))
		current_scale = 1 - current_scale;
	res = (int)(current_scale * texture->size_x);
	if (res < 0)
		res = 0;
	if (res >= texture->size_x)
		res = texture->size_x - 1;
	return (res);
}

static int	get_texture_color(t_texture *texture, t_column *column)
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
	column.y_pos = 0;
	column.y_step = (float)texture->size_y / (float)column.len;
	if (start < 0)
		start = 0;
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
