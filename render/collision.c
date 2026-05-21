/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 18:16:46 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/21 08:26:34 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int	is_wall(t_game *data, float px, float py)
{
	if ((int)px > data->map_size_x)
		return (1);
	if ((int)py > data->map_size_y)
		return (1);
	return (data->map[(int)py][(int)px] == '1');
}

int	is_move_valid(t_game *data, float px, float py)
{
	float	box;

	box = PLAYER_BUFFER;
	if (is_wall(data, px + box, py + box))
		return (0);
	if (is_wall(data, px - box, py - box))
		return (0);
	if (is_wall(data, px - box, py + box))
		return (0);
	if (is_wall(data, px + box, py - box))
		return (0);
	return (1);
}
