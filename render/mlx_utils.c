/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:36:27 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/20 09:00:15 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	put_pixel_to_img(t_test *data, int x, int y, int color)
{
	char	*addr;

	if (x < 0 || x >= WIN_W)
		return ;
	if (y < 0 || y >= WIN_H)
		return ;
	addr = data->addr + ((y * data->line_length) + (x * (data->bpp / 8)));
	*(unsigned int *)addr = color;
}

int	close_window(t_test *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img);
	mlx_destroy_window(data->mlx_ptr, data->windows_ptr);
	exit_all(data->parse, 0);
	exit(0);
}
