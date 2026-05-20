/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 18:16:46 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/20 18:23:09 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int	is_wall(t_game *data, float px, float py)
{
	if (px >= (float)data->map_size_x || px < 0.0f)
		return (1);
	if (py >= (float)data->map_size_y || py < 0.0f)
		return (1);
	return (data->map[(int)py][(int)px] == '1');
}

int	is_move_valid(t_game *data, float px, float py)
{
	float	box;

	box = PLAYER_BUFFER;
	if (is_wall(data, px, py))
		return (0);
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
