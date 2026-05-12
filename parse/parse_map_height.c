/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_height.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:38:29 by andrrand          #+#    #+#             */
/*   Updated: 2026/05/08 10:39:38 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	set_cap(t_data *data, const char *str)
{
	if (is_allcharin(str, " \n"))
		return (0);
	while (*str)
	{
		if (data->cap == 0 && ft_strchr("NSWE", *str))
			data->cap = *str;
		else if (data->cap != 0 && ft_strchr("NSWE", *str))
			return (0);
		str++;
	}
	return (1);
}

int	check_map_height(t_data *data)
{
	char	*str;
	size_t	height;

	height = 0;
	str = NULL;
	skip_labels(data);
	while (1)
	{
		str = get_next_line(data->map_fd);
		if (!str)
			break ;
		if (ft_isemptyline(str) && height == 0)
		{
			free(str);
			continue ;
		}
		if ((ft_isemptyline(str) && height > 0) || !set_cap(data, str)
			|| (!ft_isemptyline(str) && !is_allcharin(str, "10NSWE \n")))
			return (free(str), 0);
		height++;
		free(str);
	}
	data->map_height = height;
	return (height > 2 && data->cap != 0);
}
