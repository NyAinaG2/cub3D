/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 09:11:45 by andrrand          #+#    #+#             */
/*   Updated: 2026/05/23 06:42:01 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	check_texture(t_data *data, char *str, int index)
{
	char	**strs;
	int		*width;
	int		*height;

	strs = NULL;
	width = &data->img_size[index][0];
	height = &data->img_size[index][1];
	trim_newline(str);
	if (ft_countword(str, ' ') != 2)
		return (0);
	strs = ft_split(str, ' ');
	if (!strs)
		return (0);
	data->img_ptr[index] = mlx_xpm_file_to_image
		(data->mlx_ptr, strs[1], width, height);
	free_strs(strs);
	return (data->img_ptr[index] != NULL);
}

static void	get_color(t_data *data, char *str, int index)
{
	char	**strs;
	int		i;
	int		rgb[3];

	i = 0;
	strs = ft_split(str, ',');
	if (!strs)
		return ;
	while (i < 3)
	{
		rgb[i] = ft_atoi(strs[i]);
		i++;
	}
	data->colors[index - 4] = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	free_strs(strs);
}

static int	check_color(t_data *data, char *str, int index)
{
	char	**strs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	trim_newline(str);
	str += ft_check_head(data->labels[index], str);
	i = ft_countword(str, ',');
	if (ft_count_char(str, ',') != 2 || i != 3)
		return (0);
	strs = ft_split(str, ',');
	if (!strs)
		return (0);
	while (strs[j] && i == 3)
	{
		if (!is_valid_number(strs[j]))
			break ;
		j++;
	}
	free_strs(strs);
	if (i == 3 && j == 3)
		get_color(data, str, index);
	return (i == 3 && j == 3);
}

static int	check_token(t_data *data, char *str)
{
	int		i;
	int		error;

	i = 0;
	error = 0;
	while (i < 6 && !error)
	{
		if (ft_check_head(data->labels[i], str))
		{
			data->index_checker[i]++;
			error = data->index_checker[i] > 1;
			if (i <= 3 && error == 0)
				error = !check_texture(data, str, i);
			else if (error == 0)
				error = !check_color(data, str, i);
			break ;
		}
		i++;
	}
	return (error != 1 && i < 6);
}

int	check_params(t_data *data)
{
	int		line;
	char	*str;

	str = NULL;
	line = 0;
	while (line < 6)
	{
		str = get_next_line(data->map_fd);
		if (!str)
			break ;
		if (ft_isemptyline(str))
		{
			free(str);
			continue ;
		}
		if (!check_token(data, str))
		{
			free(str);
			break ;
		}
		line++;
		free(str);
	}
	return (line == 6);
}
