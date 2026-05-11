/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 18:16:46 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/11 18:58:31 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projection.h"

int	is_wall(t_test *data, float px, float py)
{
	if ((int)px > data->map_size_x)
		return (0);
	if ((int)py > data->map_size_y)
		return (0);
	return (tmp_map[(int)py][(int)px] == 1);
}

int	is_move_valid(t_test *data, float px, float py)
{
	float	box;

	box = data->player_box;
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
