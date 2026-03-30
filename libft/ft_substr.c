/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:45:07 by andrrand          #+#    #+#             */
/*   Updated: 2025/03/15 08:38:22 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;
	char	*out;
	size_t	j;

	j = 0;
	tmp = (char *)&s[start];
	if (start > ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	out = malloc(sizeof (char) * len + 1);
	if (out == NULL)
		return (NULL);
	while (j < len && tmp[j])
	{
		out[j] = tmp[j];
		j++;
	}
	out[j] = 0;
	return (out);
}
