/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:18:12 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/11 09:48:24 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projection.h"

double	clamp_time(double time, double tmax)
{
	if (time > tmax)
		return (tmax);
	return (time);
}

double	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((double)time.tv_sec + ((double)time.tv_usec) / 1000000);
}

double	get_delta_time(t_test *data)
{
	double	current_time;
	double	res;

	current_time = get_current_time();
	res = current_time - data->game_time;
	return (clamp_time(res, 1));
}
