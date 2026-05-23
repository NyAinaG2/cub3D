/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 06:19:47 by andrrand          #+#    #+#             */
/*   Updated: 2026/05/23 06:43:30 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_overflow(long result, int digit)
{
	if (result > 255 / 10 || (result == 255 / 10 && digit > 255 % 10))
		return (1);
	return (0);
}

int	is_valid_number(char *str)
{
	int		i;
	int		result;
	int		sign;

	result = 0;
	i = 0;
	sign = 1;
	if (!str || !str[0])
		return (0);
	while (str[i] == 32)
		i++;
	if (!str[i] || !ft_isdigit(str[i]) || sign == -1)
		return (0);
	while (str[i] && ft_isdigit(str[i]))
	{
		if (!ft_isdigit(str[i]) || is_overflow(result, str[i] - '0'))
			return (0);
		result = result * 10 + str[i++] - '0';
	}
	while (str[i] == 32)
		i++;
	return (str[i] == '\0');
}
