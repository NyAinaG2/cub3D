/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:43:09 by andrrand          #+#    #+#             */
/*   Updated: 2025/03/15 08:37:00 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*tab;

	i = size * nmemb;
	if (size && (i / size) != nmemb)
		return (NULL);
	tab = malloc(i);
	if (tab == NULL)
		return (NULL);
	ft_bzero(tab, i);
	return (tab);
}
