/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <adrandriamanga@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:06:13 by andrrand          #+#    #+#             */
/*   Updated: 2026/04/25 23:00:37 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	purge_get_next_line(int fd)
{
	char	*str;

	if (!fd)
		return ;
	str = get_next_line(fd);
	if (!str)
	{
		free(str);
		return ;
	}
	purge_get_next_line(fd);
	free(str);
}

char	*ft_strcpy(char *src, size_t len)
{
	size_t	i;
	char	*out;

	i = 0;
	out = malloc(sizeof (char) * len + 1);
	if (!*src || !out)
	{
		if (out)
			free(out);
		return (NULL);
	}
	while (i < len)
	{
		out[i] = src[i];
		i++;
	}
	out[len] = 0;
	return (out);
}
