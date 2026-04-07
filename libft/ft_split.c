/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <adrandriamanga@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:44:07 by andrrand          #+#    #+#             */
/*   Updated: 2026/04/04 19:25:46 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countword(char const *s, char c)
{
	int	count;

	count = 0;
	if (s == NULL)
		return (0);
	if (*s != 0 && *s != c)
		count++;
	while (*s)
	{
		if (*s == c && *(s + 1) != c && *(s + 1) != 0)
			count++;
		s++;
	}
	return (count);
}

static char	**ft_settab(char **tab, char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			i = 0;
			while (s[i] != 0 && s[i] != c)
				i++;
			tab[count] = ft_substr(s, 0, i);
			if (tab[count] == NULL)
				return (NULL);
			count++;
			s += i;
		}
		else
			s++;
	}
	tab[count] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	tab = malloc(sizeof (char *) * (ft_countword(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	tab = ft_settab(tab, s, c);
	if (tab == NULL)
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}
