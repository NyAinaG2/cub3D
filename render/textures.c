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
	float	u;
	int		res;

	if (len_column <= 0)
		return (0);
	u = (float)(current_y - start) / (float)len_column;
	res = (int)(u * texture->size_y);
	if (res < 0)
		res = 0;
	if (res >= texture->size_y)
		res = texture->size_y - 1;
	return (res);
}

int	get_texture_x(t_texture *texture, t_params *params)
{
	int	res;

	res = (int)(params->scale * texture->size_x);
	if (res < 0)
		res = 0;
	if (res >= texture->size_x)
		res = texture->size_x - 1;
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
	int			start_unclipped;
	int			y;
	t_column	column;

	column.len = len;
	start_unclipped = -len / 2 + WIN_H / 2;
	start = start_unclipped;
	end = len / 2 + WIN_H / 2;
	if (start < 0)
		start = 0;
	if (end >= WIN_H)
		end = WIN_H - 1;
	column.start = start_unclipped;
	y = start;
	while (y < end)
	{
		column.current = y;
		put_pixel_to_img(data, x, y, get_texture_color(params, &data->north,
				&column));
		y++;
	}
}
