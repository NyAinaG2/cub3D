/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:43:28 by andrrand          #+#    #+#             */
/*   Updated: 2025/03/15 08:37:13 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648 || n == 2147483647)
		return (10);
	if (n < 0)
		n = -n;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		memlen;
	char	*str;

	memlen = ft_nbrlen(n) + 1;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		memlen++;
	str = malloc(sizeof (char) * memlen);
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	str[memlen - 1] = 0;
	while (n)
	{
		str[(memlen--) - 2] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}
