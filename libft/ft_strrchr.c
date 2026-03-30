/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:44:58 by andrrand          #+#    #+#             */
/*   Updated: 2025/03/15 08:38:17 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	size_t	i;

	tmp = (char *)s;
	i = ft_strlen(tmp);
	if (c == 0)
		return (tmp + i);
	while (i--)
	{
		if (tmp[i] == (char)c)
			return (tmp + i);
	}
	return (NULL);
}
