/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:03:35 by andrrand          #+#    #+#             */
/*   Updated: 2026/05/12 14:07:39 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	init_tab_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < 6)
		data->index_checker[i++] = 0;
	i = 0;
	while (i < 4)
		data->img_ptr[i++] = NULL;
	data->pos[0] = 0;
	data->pos[1] = 0;
}

void	init_data(t_data *data, char **argv)
{
	static char	*g_labels[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};

	data->cap = 0;
	data->is_closed = 1;
	data->map_name = argv[1];
	data->map_tab = NULL;
	data->map_fd = -1;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		ft_putstr_fd(MLX_ERROR, 2);
		exit(1);
	}
	init_tab_data(data);
	data->map_height = 0;
	data->start_w = 0;
	data->end_w = 0;
	data->labels = g_labels;
}

void	ft_reset_char_map(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (data->map_tab[j])
	{
		i = 0;
		while (data->map_tab[j][i])
		{
			if (ft_strchr("3QZVH#", data->map_tab[j][i]))
				data->map_tab[j][i] -= 3;
			i++;
		}
		j++;
	}
}

void	ft_print_map(t_data *data)
{
	int	i;

	i = 0;
	ft_putstr_fd("F ", 1);
	ft_putnbr_fd(data->colors[0][0], 1);
	ft_putstr_fd(",", 1);
	ft_putnbr_fd(data->colors[0][1], 1);
	ft_putstr_fd(",", 1);
	ft_putnbr_fd(data->colors[0][2], 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("C ", 1);
	ft_putnbr_fd(data->colors[1][0], 1);
	ft_putstr_fd(",", 1);
	ft_putnbr_fd(data->colors[1][1], 1);
	ft_putstr_fd(",", 1);
	ft_putnbr_fd(data->colors[1][2], 1);
	ft_putstr_fd("\n", 1);
	while (data->map_tab[i])
	{
		ft_putstr_fd(data->map_tab[i], 1);
		ft_putstr_fd("|", 1);
		ft_putnbr_fd(i++, 1);
		ft_putstr_fd("\n", 1);
	}
	ft_putstr_fd("Player pos x = ", 1);
	ft_putnbr_fd(data->pos[0], 1);
	ft_putstr_fd(" y = ", 1);
	ft_putnbr_fd(data->pos[1], 1);
	ft_putstr_fd("\n", 1);
}

void	parse(t_data *data, char **argv)
{
	init_data(data, argv);
	check_map(data, check_params, 1, LABEL_ERROR);
	check_map(data, check_map_height, 1, MAP_ERROR);
	check_map(data, set_start_width, 1, "");
	check_map(data, set_end_width, 1, "");
	data->map_tab = init_map_tab(data);
	check_map(data, get_next_to_map, 1, "");
	check_map(data, check_map_close, 0, CLOSED_ERROR);
	ft_reset_char_map(data);
	set_player_pos(data);
	ft_print_map(data);
}
