/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 09:59:03 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/19 10:16:09 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_texture	*get_texture(t_params *params, t_test *data)
{
	if (params->side == 'y')
	{
		if (params->direction == 1)
			return (&data->north);
		else
			return (&data->south);
	}
	else
	{
		if (params->direction == 1)
			return (&data->west);
		else
			return (&data->east);
	}
	return (&data->north);
}
