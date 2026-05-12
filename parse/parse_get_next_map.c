/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get_next_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:38:23 by andrrand          #+#    #+#             */
/*   Updated: 2026/05/08 10:39:30 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	replace_to_space(t_data *data, char *str)
{
	size_t	i;

	i = 0;
	while (i < data->end_w)
		str[i++] = ' ';
	str[i] = 0;
}

char	**init_map_tab(t_data *data)
{
	char	**map_tab;
	size_t	i;

	i = 0;
	map_tab = malloc(sizeof(char *) * (data->map_height + 1));
	if (!map_tab)
		exit_parse(data, MEM_ERROR);
	while (i <= data->map_height)
		map_tab[i++] = NULL;
	i = 0;
	while (i < data->map_height)
	{
		map_tab[i] = malloc(sizeof(char) * (data->end_w + 1));
		if (!map_tab[i])
		{
			while (i > 0)
				free(map_tab[--i]);
			free(map_tab);
			map_tab = NULL;
			exit_parse(data, MEM_ERROR);
		}
		replace_to_space(data, map_tab[i]);
		i++;
	}
	return (map_tab);
}

void	get_next_to_map_core(t_data *data, char *str)
{
	static size_t	index = 0;
	size_t			i;
	size_t			len;

	i = 0;
	len = ft_strlen(str);
	while (i < data->end_w)
	{
		if (i + data->start_w < len)
			data->map_tab[index][i] = str[i + data->start_w];
		i++;
	}
	index++;
}

int	get_next_to_map(t_data *data)
{
	char	*str;

	str = NULL;
	skip_labels(data);
	while (1)
	{
		str = get_next_line(data->map_fd);
		if (!str)
			break ;
		if (ft_isemptyline(str))
		{
			free(str);
			continue ;
		}
		trim_newline(str);
		get_next_to_map_core(data, str);
		free(str);
	}
	return (1);
}
