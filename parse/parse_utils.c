/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 08:55:00 by andrrand          #+#    #+#             */
/*   Updated: 2026/05/22 17:45:51 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	trim_newline(char *str)
{
	if (!str)
		return ;
	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = 0;
}

int	is_allcharin(const char *source, const char *str)
{
	while (*source)
	{
		if (!ft_strchr(str, *source++))
			return (0);
	}
	return (1);
}

int	ft_isemptyline(const char *str)
{
	return (str && ft_strlen(str) == 1 && *str == '\n');
}

int	ft_check_head(char *src, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j] == ' ')
		j++;
	while (src[i] == str[j])
	{
		i++;
		j++;
	}
	if (str[j] == ' ' && !src[i])
		return (j);
	return (0);
}

size_t	ft_count_char(const char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
