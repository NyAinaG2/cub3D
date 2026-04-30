/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:03:39 by mrakotos          #+#    #+#             */
/*   Updated: 2026/04/30 18:02:34 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projection.h"

int init(t_test* data_ptr)
{
	/* int temp[6][6] = {{1, 1, 1, 1, 1, 1},
					  {1, 0, 0, 0, 0, 1},
					  {1, 0, 0, 1, 0, 1},
					  {1, 0, 0, 0, 0, 1},
					  {1, 1, 1, 1, 1, 1}}; */

	data_ptr->mlx_ptr = mlx_init();
	if (!data_ptr->mlx_ptr) return (0);
	data_ptr->windows_ptr =
		mlx_new_window(data_ptr->mlx_ptr, WIN_W, WIN_H, WIN_TITLE);
	if (!data_ptr->windows_ptr) return (0);
	data_ptr->img = mlx_new_image(data_ptr->mlx_ptr, WIN_W, WIN_H);
	data_ptr->addr = mlx_get_data_addr(data_ptr->img,
									   &data_ptr->bpp,
									   &data_ptr->line_length,
									   &data_ptr->endian);
	return (1);
}
