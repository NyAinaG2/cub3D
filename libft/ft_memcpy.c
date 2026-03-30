/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:43:37 by andrrand          #+#    #+#             */
/*   Updated: 2025/03/15 08:37:38 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*out;
	const unsigned char	*temp;

	i = 0;
	out = (unsigned char *)dest;
	temp = (const unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		out[i] = temp[i];
		i++;
	}
	return ((void *)out);
}
