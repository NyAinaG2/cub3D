/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:44:55 by andrrand          #+#    #+#             */
/*   Updated: 2025/03/15 08:38:15 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	tmp = (char *)big;
	i = 0;
	j = 0;
	if (*little == 0)
		return (tmp);
	if (ft_strlen(big) < len)
		len = ft_strlen(big);
	while (*tmp && i < len)
	{
		if (tmp[i] == little[0])
		{
			j = 0;
			while (tmp[i + j] == little[j] && little[j] && i + j < len)
				j++;
			if (little[j] == 0)
				return (tmp + i);
		}
		i++;
	}
	return (NULL);
}
