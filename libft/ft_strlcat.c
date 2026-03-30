/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:44:40 by andrrand          #+#    #+#             */
/*   Updated: 2025/03/15 08:38:04 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lensrc;
	size_t	lendest;
	size_t	i;

	lensrc = ft_strlen(src);
	lendest = ft_strlen(dst);
	i = 0;
	if (size == 0 || size <= lendest)
		return (size + lensrc);
	while (i < size - lendest - 1 && src[i] != 0)
	{
		dst[lendest + i] = src[i];
		i++;
	}
	dst[lendest + i] = 0;
	return (lensrc + lendest);
}
