/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:37:13 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/18 19:41:06 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	sample_texture(t_texture *texture, int x, int y)
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

int	get_texture_y(t_texture *texture, int current_y, int start, int len_column)
{
	int	res;

	if (len_column <= 0)
		return (0);
	res = (float)(current_y - start) / (float)len_column;
	res = (int)(res * texture->size_y);
	if (res < 0)
		res = 0;
	if (res >= texture->size_y)
		res = texture->size_y - 1;
	return (res);
}

int	get_texture_x(t_texture *texture, t_params *params)
{
	int	res;

	if (params->scale == 1)
		return (texture->size_x - 1);
	if (params->scale == 0)
		return (0);
	res = (int)(params->scale * texture->size_x);
	return (res);
}

int	get_texture_color(t_params *params, t_texture *texture, t_column *column)
{
	int	x;
	int	y;
	int	res;

	x = get_texture_x(texture, params);
	y = get_texture_y(texture, column->current, column->start, column->len);
	res = sample_texture(texture, x, y);
	return (res);
}

void	draw_column(int len, int x, t_test *data, t_params *params)
{
	int			start;
	int			end;
	t_column	column;

	column.len = len;
	start = -len / 2 + WIN_H / 2;
	end = len / 2 + WIN_H / 2;
	column.current = start;
	if (start < 0)
		start = 0;
	if (end >= WIN_H)
		end = WIN_H - 1;
	column.start = start;
	while (start < end)
	{
		put_pixel_to_img(data, x, start, get_texture_color(params, &data->north,
				&column));
		column.current++;
		start++;
	}
}
