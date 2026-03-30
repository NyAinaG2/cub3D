/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:45:02 by andrrand          #+#    #+#             */
/*   Updated: 2025/03/15 08:38:20 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(int c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;

	i = 0;
	while (ft_isinset(*s1, set))
		s1++;
	i = ft_strlen(s1) - 1;
	while (ft_isinset(s1[i], set) && i > 0)
		i--;
	return (ft_substr(s1, 0, i + 1));
}
