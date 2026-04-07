/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <adrandriamanga@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:44:07 by andrrand          #+#    #+#             */
/*   Updated: 2026/04/04 18:40:24 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static int	ft_is_delimiter(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	ft_countword_new(char const *s, char *str)
{
	int	count;

	count = 0;
	if (s == NULL)
		return (0);
	if (*s != 0 && !ft_is_delimiter(*s, str))
		count++;
	while (*s)
	{
		if (ft_is_delimiter(*s, str) && !ft_is_delimiter(*(s + 1), str) && *(s + 1) != 0)
			count++;
		s++;
	}
	return (count);
}

static char	**ft_settab_new(char **tab, char const *s, char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (*s)
	{
		if (!ft_is_delimiter(*s, str))
		{
			i = 0;
			while (s[i] != 0 && !ft_is_delimiter(s[i], str))
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

char	**ft_split_new(char const *s, char *str)
{
	char	**tab;

	tab = malloc(sizeof (char *) * (ft_countword_new(s, str) + 1));
	if (tab == NULL)
		return (NULL);
	tab = ft_settab_new(tab, s, str);
	if (tab == NULL)
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}
