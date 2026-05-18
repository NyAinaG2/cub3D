/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:37:13 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/18 18:30:28 by mrakotos         ###   ########.fr       */
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

int	get_texture_color(t_params *params, t_texture *texture)
{
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
