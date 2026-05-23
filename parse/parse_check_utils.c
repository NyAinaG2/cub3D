/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:38:16 by andrrand          #+#    #+#             */
/*   Updated: 2026/05/23 06:41:46 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_check_extension(char *str)
{
	char	**strs;
	size_t	len;
	size_t	i;

	strs = ft_split(str, '/');
	i = 0;
	if (!strs)
	{
		ft_putstr_fd(MEM_ERROR, 2);
		exit(1);
	}
	while (strs[i])
		i++;
	if (i == 0)
		return (free_strs(strs), 0);
	len = ft_strlen(strs[i - 1]);
	if (len < 5)
		return (free_strs(strs), 0);
	if (ft_strncmp(strs[i - 1] + (len - 4), ".cub", 4) != 0)
		return (free_strs(strs), 0);
	return (free_strs(strs), 1);
}

void	check_map(t_data *data, int (*f)(t_data *), int o, char *msg)
{
	if (o)
	{
		data->map_fd = open(data->map_name, O_RDONLY);
		if (data->map_fd < 0)
			exit_parse(data, FD_ERROR);
		if (!f(data))
		{
			purge_get_next_line(data->map_fd);
			close(data->map_fd);
			exit_parse(data, msg);
		}
		purge_get_next_line(data->map_fd);
		close(data->map_fd);
		return ;
	}
	if (!f(data))
		exit_parse(data, msg);
}

void	skip_labels(t_data *data)
{
	int		line;
	char	*str;

	str = NULL;
	line = 0;
	while (line < 6)
	{
		str = get_next_line(data->map_fd);
		if (!str)
			break ;
		if (ft_isemptyline(str))
		{
			free(str);
			continue ;
		}
		line++;
		free(str);
	}
}
