/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:15:03 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/11 11:01:21 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "projection/projection.h"

const unsigned char	tmp_map[7][6] = {{1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 1}, {1,
		0, 1, 0, 0, 1}, {1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0,
		1}, {1, 1, 1, 1, 1, 1}};

int	main(void)
{
	t_test	data;

	data.map = (unsigned char **)tmp_map;
	init(&data);
	draw(&data);
	mlx_hook(data.windows_ptr, 2, 1L << 0, key_press, &data);
	mlx_hook(data.windows_ptr, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx_ptr, move, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
