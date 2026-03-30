/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:44:20 by andrrand          #+#    #+#             */
/*   Updated: 2025/03/15 08:37:56 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*str;

	i = 0;
	str = malloc(sizeof (char) * ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	while (i < ft_strlen(s))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
