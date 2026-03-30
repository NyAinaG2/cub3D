/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:43:42 by andrrand          #+#    #+#             */
/*   Updated: 2025/03/13 10:43:32 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*tmp;
	unsigned char		*out;

	tmp = (const unsigned char *)src;
	out = (unsigned char *)dest;
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	while (n--)
		out[n] = tmp[n];
	return ((void *)out);
}
