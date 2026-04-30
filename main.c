/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:15:03 by mrakotos          #+#    #+#             */
/*   Updated: 2026/04/30 19:15:10 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main()
{
	t_test data;

	if (init(&data)) printf("OK\n");
	draw(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
