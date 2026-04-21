/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:03:35 by andrrand          #+#    #+#             */
/*   Updated: 2026/04/21 10:27:57 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include "cub3d.h"

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

void	exit_error(t_data *data, char *msg)
{
	(void)data;
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	if (data->map_tab)
		free_strs(data->map_tab);
	exit(1);
}

int	is_allcharin(const char *source, const char *str)
{
	while (*source)
	{
		if (!ft_strchr(str, *source++))
			return (0);
	}
	return (1);
}

int	ft_check_extension(char *str)
{
	char	**strs;
	size_t	len;
	size_t	i;

	strs = ft_split(str, '/');
	i = 0;
	while (strs[i])
		i++;
	if (i == 0)
		return (free_strs(strs),0);
	len = ft_strlen(strs[i - 1]);
	if (len < 5)
		return (free_strs(strs), 0);
	if (ft_strncmp(strs[i - 1] + (len - 4), ".cub", 4) != 0)
		return (free_strs(strs), 0);
	return (free_strs(strs),1);
}

int	ft_isemptyline(const char *str)
{
	return (str && ft_strlen(str) == 1 && *str == '\n');
}

void	check_from_file(t_data *data, int (*f)(t_data *), int o, char *msg)
{
	if (o)
	{
		data->map_fd = open(data->map_name, O_RDONLY);
		if (data->map_fd < 0)
			exit_error(data, "Fail to open the map file");
		if (!f(data))
		{
			purge_get_next_line(data->map_fd);
			close(data->map_fd);
			exit_error(data, msg);
		}
		purge_get_next_line(data->map_fd);
		close(data->map_fd);
		return ;
	}
	if (!f(data))
		exit_error(data, msg);
}

void	check_map_attribute(t_data *data, int (*f)(t_data *data), char *msg)
{
	if (!f(data))
		exit_error(data, msg);
}

int	check_fd(char *str)
{
	int	fd;

	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = 0;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	check_color(char *str)
{
	char	**strs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = 0;
	strs = ft_split(str, ',');
	while (strs[i])
		i++;
	while (strs[j] && i == 3)
	{
		if (ft_atoi(strs[j]) > 255 || ft_atoi(strs[j]) < 0
			|| !is_allcharin(strs[j], "1234567890"))
			break ;
		j++;
	}
	free_strs(strs);
	return (i == 3 && j == 3);
}

int	check_labels_unit(t_data *data, char *str)
{
	char	**strs;
	int		i;
	int		error;

	i = 0;
	error = 0;
	strs = ft_split(str, ' ');
	while (i < 6 && !error)
	{
		if (ft_strncmp(TEX_LABELS_STATIC[i], strs[0], ft_strlen(strs[0])) == 0)
		{
			data->index_checker[i]++;
			error = data->index_checker[i] > 1;
			if (i <= 3 && error == 0)
				error = !check_fd(strs[1]);
			else if (error == 0)
				error = !check_color(strs[1]);
			break ;
		}
		i++;
	}
	free_strs(strs);
	return (error != 1 && i < 6);
}

int	check_labels(t_data *data)
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
		if ((ft_countword(str, ' ') != 2 && line < 6)
			|| !check_labels_unit(data, str))
		{
			free(str);
			break ;
		}
		line++;
		free(str);
	}
	return (line == 6);
}

void	skip_labels(t_data *data)
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
		line++;
		free(str);
	}
}

int	set_cap(t_data *data, const char *str)
{
	if (is_allcharin(str, " \n"))
		return (0);
	while (*str)
	{
		if (data->cap == 0 && ft_strchr("NOWE", *str))
			data->cap = *str;
		else if (data->cap != 0 && ft_strchr("NOWE", *str))
			return (0);
		str++;
	}
	return (1);
}

int	check_map_height(t_data *data)
{
	char	*str;
	size_t	height;

	height = 0;
	str = NULL;
	skip_labels(data);
	while (1)
	{
		str = get_next_line(data->map_fd);
		if (!str)
			break ;
		if (ft_isemptyline(str) && height == 0)
		{
			free(str);
			continue ;
		}
		if ((ft_isemptyline(str) && height > 0) || !set_cap(data, str)
			|| (!ft_isemptyline(str) && !is_allcharin(str, "10NOWE \n")))
		{
			free(str);
			return (0);
		}
		height++;
		free(str);
	}
	data->map_height = height;
	return (height > 2 && data->cap != 0);
}

size_t	count_first_space(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

size_t	count_rear_space(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str) - 1;
	if (str[ft_strlen(str) - 1] == '\n')
	{
		str[ft_strlen(str) - 1] = 0;
		len--;
	}
	while (len && str[len] == ' ')
	{
		len--;
		i++;
	}
	return (i);
}

int	set_start_width(t_data *data)
{
	char	*str;
	size_t	start;
	size_t	start_width;

	start_width = 0;
	str = NULL;
	start = 0;
	skip_labels(data);
	while (1)
	{
		str = get_next_line(data->map_fd);
		if (!str)
			break ;
		if (ft_isemptyline(str) && start_width == 0)
		{
			free(str);
			continue ;
		}
		if (start++ == 0)
			start_width = count_first_space(str);
		if (start_width > count_first_space(str))
			start_width = count_first_space(str);
		free(str);
	}
	data->start_width = start_width;
	return (1);
}

int	set_end_width(t_data *data)
{
	char	*str;
	size_t	start;
	size_t	end_width;

	end_width = 0;
	str = NULL;
	start = 0;
	skip_labels(data);
	while (1)
	{
		str = get_next_line(data->map_fd);
		if (!str)
			break ;
		if (ft_isemptyline(str) && end_width == 0)
		{
			free(str);
			continue ;
		}
		if (str[ft_strlen(str) - 1] == '\n')
			str[ft_strlen(str) - 1] = 0;
		if (start++ == 0 || end_width < ft_strlen(str) - data->start_width - count_rear_space(str))
			end_width = ft_strlen(str) - data->start_width - count_rear_space(str);
		free(str);
	}
	data->end_width = end_width;
	return (1);
}

void	replace_to_space(t_data *data, char *str)
{
	size_t	i;

	i = 0;
	while (i < data->end_width)
		str[i++] = ' ';
	str[i] = 0;
}

char	**init_map_tab(t_data *data)
{
	char	**map_tab;
	size_t	i;

	i = 0;
	map_tab = malloc(sizeof(char *) * (data->map_height + 1));
	if (!map_tab)
		return (NULL);
	while (i <= data->map_height)
		map_tab[i++] = NULL;
	i = 0;
	while (i < data->map_height)
	{
		map_tab[i] = malloc(sizeof(char) * (data->end_width + 1));
		if (!map_tab[i])
		{
			while (i > 0)
				free(map_tab[--i]);
			free(map_tab);
			map_tab = NULL;
			return (NULL);
		}
		replace_to_space(data, map_tab[i]);
		i++;
	}
	return (map_tab);
}

void	get_next_to_map_core(t_data *data, char *str)
{
	static size_t	index = 0;
	size_t			i;
	size_t			len;

	i = 0;
	len = ft_strlen(str);
	while (i < data->end_width)
	{
		if (i + data->start_width < len)
			data->map_tab[index][i] = str[i + data->start_width];
		i++;
	}
	index++;
}

int	get_next_to_map(t_data *data)
{
	char	*str;

	str = NULL;
	skip_labels(data);
	while (1)
	{
		str = get_next_line(data->map_fd);
		if (!str)
			break ;
		if (ft_isemptyline(str))
		{
			free(str);
			continue ;
		}
		if (str[ft_strlen(str) - 1] == '\n')
			str[ft_strlen(str) - 1] = 0;
		get_next_to_map_core(data, str);
		free(str);
	}
	return (1);
}

int	check_map_close_core(t_data *data, size_t i, size_t j)
{
	if (data->map_tab[j][i] == '0' || data->map_tab[j][i] == data->cap)
	{
		if ((j == data->map_height - 1 || j == 0)
			|| (i == data->end_width - 1 || i == 0))
			return (0);
		if ((data->map_tab[j + 1][i] == ' ')
			|| (data->map_tab[j - 1][i] == ' '))
			return (0);
		if ((data->map_tab[j][i + 1] == ' ')
			|| (data->map_tab[j][i - 1] == ' '))
			return (0);
	}
	return (1);
}


int	check_map_close(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < data->end_width)
	{
		j = 0;
		while (j < data->map_height)
		{
			if (!check_map_close_core(data, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

size_t	check_map_gap_core(t_data *data, size_t i, size_t j, size_t *count)
{
	if (data->map_tab[j][i] == ' ')
		return (0);
	data->map_tab[j][i] += 3;
	if (i + 1 < data->end_width && ft_strchr("10NOWE", data->map_tab[j][i + 1]))
		check_map_gap_core(data, i + 1, j, count);
	if (j + 1 < data->map_height && ft_strchr("10NOWE", data->map_tab[j + 1][i]))
		check_map_gap_core(data, i, j + 1, count);
	if (i > 0 && ft_strchr("10NOWE", data->map_tab[j][i - 1]))
		check_map_gap_core(data, i - 1, j, count);
	if (j > 0 && ft_strchr("10NOWE", data->map_tab[j - 1][i]))
		check_map_gap_core(data, i, j - 1, count);
	if (i + 1 < data->end_width && j + 1 < data->map_height && ft_strchr("10NOWE", data->map_tab[j + 1][i + 1]))
		check_map_gap_core(data, i + 1, j + 1, count);
	if (j + 1 < data->map_height && i > 0 && ft_strchr("10NOWE", data->map_tab[j + 1][i - 1]))
		check_map_gap_core(data, i - 1, j + 1, count);
	if (j > 0 && i + 1 < data->end_width && ft_strchr("10NOWE", data->map_tab[j - 1][i + 1]))
		check_map_gap_core(data, i + 1, j - 1, count);
	if (j > 0 && i > 0 && ft_strchr("10NOWE", data->map_tab[j - 1][i - 1]))
		check_map_gap_core(data, i - 1, j - 1, count);
	(*count) += 1;
	return (*count);
}

size_t	check_map_gap(t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	j = 0;
	count = 0;
	while (i < data->end_width)
	{
		j = 0;
		while (j < data->map_height)
		{
			if (data->map_tab[j][i] == data->cap)
				return (check_map_gap_core(data, i, j, &count));
			j++;
		}
		i++;
	}
	return (count);
}

int	check_isolated_part(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < data->end_width)
	{
		j = 0;
		while (j < data->map_height)
		{
			if (data->map_tab[j][i] != ' ' && ft_strchr("10NOWE", data->map_tab[j][i]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	init_data(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->cap = 0;
	data->map_name = argv[1];
	data->map_tab = NULL;
	data->map_fd = -1;
	while (i < 3)
	{
		data->floor_color[i] = 0;
		data->ceil_color[i++] = 0;
	}
	i = 0;
	while (i < 6)
		data->index_checker[i++] = 0;
	data->map_height = 0;
	data->start_width = 0;
	data->end_width = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data, argv);
	if (argc != 2)
		exit_error(&data, "Arguments count error");
	if (!ft_check_extension(argv[1]))
		exit_error(&data, "Not extended with .cub");
	check_from_file(&data, check_labels, 1, "Map 6 elements error");
	check_from_file(&data, check_map_height, 1, "Map height error");
	check_from_file(&data, set_start_width, 1, "");
	check_from_file(&data, set_end_width, 1, "");
	data.map_tab = init_map_tab(&data);
	if (!data.map_tab)
		return (0);
	check_from_file(&data, get_next_to_map, 1, "");
	check_from_file(&data, check_map_close, 0, "Map is not closed");
	// printf("count = %zu\n", check_map_gap(&data));
	for (size_t i = 0; data.map_tab[i]; i++)
		printf("%s|%zu\n", data.map_tab[i], i);
	// printf("check_isolated_part = %i\n", check_isolated_part(&data));
	free_strs(data.map_tab);
	return (0);
}
