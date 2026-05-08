/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exit_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 08:56:47 by andrrand          #+#    #+#             */
/*   Updated: 2026/05/08 10:39:24 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
		free(strs[i++]);
	free(strs[i]);
	free(strs);
	strs = NULL;
}

void	exit_all(t_data *data, int value)
{
	int	i;

	i = 0;
	if (data->map_fd > 0)
	{
		purge_get_next_line(data->map_fd);
		close(data->map_fd);
	}
	if (data->map_tab != NULL)
		free_strs(data->map_tab);
	while (i < 4)
	{
		if (data->img_ptr[i] != NULL)
			mlx_destroy_image(data->mlx_ptr, data->img_ptr[i]);
		i++;
	}
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(value);
}

void	exit_parse(t_data *data, char *msg)
{
	ft_putstr_fd(msg, 2);
	exit_all(data, 1);
	exit(1);
}
