/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 09:10:45 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/20 11:38:34 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	init_index_texture(t_data *parse, t_texture *texture, int i)
{
	texture->img = parse->img_ptr[i];
	texture->addr = mlx_get_data_addr(parse->img_ptr[i], &texture->bpp,
			&texture->line_length, &texture->endian);
	texture->size_x = parse->img_size[i][0];
	texture->size_y = parse->img_size[i][1];
}

void	init_textures(t_data *parse, t_game *data)
{
	init_index_texture(parse, &data->north, 0);
	init_index_texture(parse, &data->south, 1);
	init_index_texture(parse, &data->west, 2);
	init_index_texture(parse, &data->east, 3);
}
