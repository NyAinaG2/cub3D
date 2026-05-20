/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 06:41:56 by andrrand          #+#    #+#             */
/*   Updated: 2026/05/20 19:12:52 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	update_game_time(t_game *data)
{
	double	tmp;
	double	delta;

	tmp = get_time();
	delta = tmp - data->last_frame;
	if (delta > 0.1f)
		data->game_time = 0.1f;
	else
		data->game_time = delta;
	data->last_frame = tmp;
}
