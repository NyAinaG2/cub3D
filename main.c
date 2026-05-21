/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:15:03 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/21 12:09:11 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/parse.h"
#include "render/render.h"

int	main(int argc, char **argv)
{
	t_game	var;
	t_data	data;

	if (argc != 2)
		return (ft_putstr_fd(ARG_ERROR, 2), 1);
	if (!ft_check_extension(argv[1]))
		return (ft_putstr_fd(EXT_ERROR, 2), 1);
	parse(&data, argv);
	if (!data.map_tab)
		return (0);
	init_render(&var, &data);
	render(&var);
	mlx_hook(var.windows_ptr, 2, 1L << 0, key_press, &var);
	mlx_hook(var.windows_ptr, 3, 1L << 1, key_release, &var);
	mlx_hook(var.windows_ptr, 17, 0, close_window, &var);
	mlx_hook(var.windows_ptr, 10, 1L << 21, focus_out, &var);
	mlx_loop_hook(var.mlx_ptr, move, &var);
	mlx_loop(var.mlx_ptr);
	return (0);
}
