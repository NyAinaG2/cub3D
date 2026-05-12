/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:38:26 by andrrand          #+#    #+#             */
/*   Updated: 2026/05/08 10:39:34 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	check_map_close_core(t_data *data, size_t i, size_t j)
{
	if (!data->is_closed || ft_strchr("13QZVH#", data->map_tab[j][i]))
		return ;
	if (j == 0 || j >= data->map_height - 1 || i == 0 || i >= data->end_w - 1)
	{
		data->is_closed = 0;
		return ;
	}
	if (ft_strchr("NWSE0 ", data->map_tab[j][i]))
		data->map_tab[j][i] += 3;
	if (j > 0)
		check_map_close_core(data, i, j - 1);
	if (j < data->map_height -1)
		check_map_close_core(data, i, j + 1);
	if (i > 0)
		check_map_close_core(data, i - 1, j);
	if (i < data->end_w -1)
		check_map_close_core(data, i + 1, j);
}

int	check_map_close(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < data->end_w)
	{
		j = 0;
		while (j < data->map_height)
		{
			if (ft_strchr("NWSE0", data->map_tab[j][i]))
				check_map_close_core(data, i, j);
			if (!data->is_closed)
				break ;
			j++;
		}
		if (!data->is_closed)
			break ;
		i++;
	}
	return (data->is_closed);
}
