/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 12:31:46 by andrrand          #+#    #+#             */
/*   Updated: 2026/05/08 12:32:34 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/parse.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_putstr_fd(ARG_ERROR, 2), 1);
	if (!ft_check_extension(argv[1]))
		return (ft_putstr_fd(EXT_ERROR, 2), 1);
	parse(&data, argv);
	exit_all(&data, 0);
	return (0);
}
