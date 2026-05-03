/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:15:03 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/03 09:07:24 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const unsigned char tmp_map[7][6] = {{1, 1, 1, 1, 1, 1},
									 {1, 0, 0, 0, 0, 1},
									 {1, 0, 1, 0, 0, 1},
									 {1, 0, 0, 0, 0, 1},
									 {1, 0, 0, 0, 0, 1},
									 {1, 0, 0, 0, 0, 1},
									 {1, 1, 1, 1, 1, 1}};

int main()
{
	t_test data;

	data.map = (unsigned char**)tmp_map;

	if (init(&data)) printf("OK\n");
	draw(&data);
	mlx_key_hook(data.windows_ptr, key_handler, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
