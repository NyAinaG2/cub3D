/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 09:10:45 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/19 09:15:44 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	init_north_texture(t_data *parse, t_texture *north)
{
	north->img = parse->img_ptr[0];
	north->addr = mlx_get_data_addr(parse->img_ptr[0], &north->bpp,
			&north->line_length, &north->endian);
	north->size_x = parse->img_size[0][0];
	north->size_y = parse->img_size[0][1];
}

static void	init_south_texture(t_data *parse, t_texture *south)
{
}

static void	init_east_texture(t_data *parse, t_texture *east)
{
}

static void	init_west_texture(t_data *parse, t_texture *west)
{
}
