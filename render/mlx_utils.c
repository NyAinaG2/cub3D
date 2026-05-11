/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:36:27 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/11 20:05:26 by mrakotos         ###   ########.fr       */
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
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}
