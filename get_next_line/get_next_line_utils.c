/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:06:13 by andrrand          #+#    #+#             */
/*   Updated: 2026/03/30 14:08:46 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
