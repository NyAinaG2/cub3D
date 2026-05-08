/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:38:37 by andrrand          #+#    #+#             */
/*   Updated: 2026/05/08 10:39:53 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static size_t	cf_space(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

static size_t	cr_space(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str) - 1;
	if (str[ft_strlen(str) - 1] == '\n')
	{
		str[ft_strlen(str) - 1] = 0;
		len--;
	}
	while (len && str[len] == ' ')
	{
		len--;
		i++;
	}
	return (i);
}

int	set_start_width(t_data *data)
{
	char	*str;
	size_t	start;
	size_t	start_width;

	start_width = 0;
	str = NULL;
	start = 0;
	skip_labels(data);
	while (1)
	{
		str = get_next_line(data->map_fd);
		if (!str)
			break ;
		if (ft_isemptyline(str) && start_width == 0)
		{
			free(str);
			continue ;
		}
		if (start++ == 0)
			start_width = cf_space(str);
		if (start_width > cf_space(str))
			start_width = cf_space(str);
		free(str);
	}
	return (data->start_w = start_width, 1);
}

int	set_end_width(t_data *data)
{
	char	*str;
	size_t	start;
	size_t	end_w;

	end_w = 0;
	str = NULL;
	start = 0;
	skip_labels(data);
	while (1)
	{
		str = get_next_line(data->map_fd);
		if (!str)
			break ;
		if (ft_isemptyline(str) && end_w == 0)
		{
			free(str);
			continue ;
		}
		trim_newline(str);
		if (start++ == 0
			|| end_w < ft_strlen(str) - data->start_w - cr_space(str))
			end_w = ft_strlen(str) - data->start_w - cr_space(str);
		free(str);
	}
	return (data->end_w = end_w, 1);
}
