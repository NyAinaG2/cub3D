/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 09:59:03 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/19 10:40:56 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

float	set_player_direction(char direction)
{
	if (direction == 'S')
		return (1.57);
	if (direction == 'N')
		return (-1.57);
	if (direction == 'E')
		return (3.14);
	if (direction == 'W')
		return (0);
	return (0);
}

t_texture	*get_texture(t_params *params, t_test *data)
{
	if (params->side == 'y')
	{
		if (params->direction == 1)
			return (&data->south);
		else
			return (&data->north);
	}
	else
	{
		if (params->direction == 1)
			return (&data->east);
		else
			return (&data->west);
	}
	return (&data->north);
}
