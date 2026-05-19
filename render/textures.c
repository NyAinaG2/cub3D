/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:37:13 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/19 17:47:54 by mrakotos         ###   ########.fr       */
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

int	get_texture_y(t_texture *texture, t_column *column)
{
	int	res;

	if (column->len <= 0)
		return (0);
	res = (int)(column->y_pos);
	if (res < 0)
		res = 0;
	if (res >= texture->size_y)
		res = texture->size_y - 1;
	return (res);
}

int	get_texture_x(t_texture *texture, t_params *params)
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
