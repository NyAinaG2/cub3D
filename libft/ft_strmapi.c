/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:44:48 by andrrand          #+#    #+#             */
/*   Updated: 2025/03/15 08:38:11 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*str;

	i = 0;
	str = ft_strdup(s);
	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	while (i < len)
	{
		str[i] = f(i, str[i]);
		i++;
	}
	return (str);
}
