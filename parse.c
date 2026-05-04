/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <adrandriamanga@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:03:35 by andrrand          #+#    #+#             */
/*   Updated: 2026/05/04 22:19:00 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
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

void	trim_newline(char *str)
{
	if(!str)
		return ;
	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = 0;
}

void	exit_all(t_data *data, int value)
{
	int	i;

	i = 0;
	if(data->map_fd > 0)
	{
		purge_get_next_line(data->map_fd);
		close(data->map_fd);
	}
	if (data->map_tab != NULL)
		free_strs(data->map_tab);
	if (data->labels)
		free_strs(data->labels);
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

int	is_allcharin(const char *source, const char *str)
{
	while (*source)
	{
		if (!ft_strchr(str, *source++))
			return (0);
	}
	return (1);
}

int	ft_isemptyline(const char *str)
{
	return (str && ft_strlen(str) == 1 && *str == '\n');
}

//---------------end parse utils-----------

int	ft_check_extension(char *str)
{
	char	**strs;
	size_t	len;
	size_t	i;

	strs = ft_split(str, '/');
	i = 0;
	if (!strs)
	{
		ft_putstr_fd(MEM_ERROR, 2);
		exit(1);
	}
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

void	check_map(t_data *data, int (*f)(t_data *), int o, char *msg)
{
	if (o)
	{
		data->map_fd = open(data->map_name, O_RDONLY);
		if (data->map_fd < 0)
			exit_parse(data, FD_ERROR);
		if (!f(data))
		{
			purge_get_next_line(data->map_fd);
			close(data->map_fd);
			exit_parse(data, msg);
		}
		purge_get_next_line(data->map_fd);
		close(data->map_fd);
		return ;
	}
	if (!f(data))
		exit_parse(data, msg);
}

int	ft_check_head(char *src, char *str)
{
	int	i;

	i = 0;
	while (*str == ' ')
		str++;
	while (src[i] == str[i])
		i++;
	if (str[i] == ' ' && !src[i])
		return (i);
	return (0);
}

int	check_texture(t_data *data, char *str, int index)
{
	char	**strs;

	strs = NULL;
	trim_newline(str);
	if (ft_countword(str, ' ') != 2)
		return (0);
	strs = ft_split(str, ' ');
	if (!strs)
		return (0);
	data->img_ptr[index] = mlx_xpm_file_to_image(data->mlx_ptr, strs[1], &data->img_size[index][0], &data->img_size[index][1]);
	free_strs(strs);
	return (data->img_ptr[index] != NULL);
}

size_t	ft_count_char(const char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	get_color(t_data *data, char *str, int index)
{
	char	**strs;
	int		i;

	i = 0;
	strs = ft_split(str, ',');
	if (!strs)
		return ;
	while (i < 3)
	{
		data->colors[index - 4][i] = ft_atoi(strs[i]);
		i++;
	}
	free_strs(strs);
}

int	check_color(t_data *data, char *str, int index)
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
	if(!strs)
		return (0);
	while (strs[j] && i == 3)
	{
		if (ft_atoi(strs[j]) > 255 || ft_atoi(strs[j]) < 0
			|| !is_allcharin(strs[j], "1234567890 ") || ft_countword(strs[j], ' ') != 1)
			break ;
		j++;
	}
	free_strs(strs);
	if(i == 3 && j == 3)
		get_color(data, str, index);
	return (i == 3 && j == 3);
}

int	check_token(t_data *data, char *str)
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
		if (data->cap == 0 && ft_strchr("NSWE", *str))
			data->cap = *str;
		else if (data->cap != 0 && ft_strchr("NSWE", *str))
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
			|| (!ft_isemptyline(str) && !is_allcharin(str, "10NSWE \n")))
			return (free(str), 0);
		height++;
		free(str);
	}
	data->map_height = height;
	return (height > 2 && data->cap != 0);
}

size_t	cf_space(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

size_t	cr_space(char *str)
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
			start_width = cf_space(str);
		if (start_width > cf_space(str))
			start_width = cf_space(str);
		free(str);
	}
	data->start_w = start_width;
	return (1);
}

int	set_end_width(t_data *data)
{
	char	*str;
	size_t	start;
	size_t	end_w;

	end_w = 0;
	str = NULL;
	start = 0;
	skip_labels(data);
	while (1)
	{
		str = get_next_line(data->map_fd);
		if (!str)
			break ;
		if (ft_isemptyline(str) && end_w == 0)
		{
			free(str);
			continue ;
		}
		trim_newline(str);
		if (start++ == 0 || end_w < ft_strlen(str) - data->start_w - cr_space(str))
			end_w = ft_strlen(str) - data->start_w - cr_space(str);
		free(str);
	}
	data->end_w = end_w;
	return (1);
}

void	replace_to_space(t_data *data, char *str)
{
	size_t	i;

	i = 0;
	while (i < data->end_w)
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
		exit_parse(data, MEM_ERROR);
	while (i <= data->map_height)
		map_tab[i++] = NULL;
	i = 0;
	while (i < data->map_height)
	{
		map_tab[i] = malloc(sizeof(char) * (data->end_w + 1));
		if (!map_tab[i])
		{
			while (i > 0)
				free(map_tab[--i]);
			free(map_tab);
			map_tab = NULL;
			exit_parse(data, MEM_ERROR);
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
	while (i < data->end_w)
	{
		if (i + data->start_w < len)
			data->map_tab[index][i] = str[i + data->start_w];
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
		trim_newline(str);
		get_next_to_map_core(data, str);
		free(str);
	}
	return (1);
}

void	check_map_close_core(t_data *data, size_t i, size_t j)
{
	if(!data->is_closed || ft_strchr("13QZVH", data->map_tab[j][i]))
		return ;
	if (j == 0 || j >= data->map_height - 1 || i == 0 || i >= data->end_w - 1)
	{
		data->is_closed = 0;
		return ;
	}
	if(data->map_tab[j][i] == ' ')
		data->map_tab[j][i] = '-';
	if(strchr("NWSE0", data->map_tab[j][i]))
		data->map_tab[j][i] += 3;
	if (j > 0)
		check_map_close_core_new(data, i, j - 1);
	if (j < data->map_height -1)
		check_map_close_core_new(data, i, j + 1);
	if (i > 0)
		check_map_close_core_new(data, i - 1, j);
	if (i < data->end_w -1)
		check_map_close_core_new(data, i + 1, j);
}

int	check_map_close(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < data->end_w)
	{
		j = 0;
		while (j < data->map_height)
		{
			if(strchr("NWSE0", data->map_tab[j][i]))
				check_map_close_core_new(data, i, j);
			if(!data->is_closed)
				break ;
			j++;
		}
		if(!data->is_closed)
			break ;
		i++;
	}
	return (data->is_closed);
}

void	init_data(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->cap = 0;
	data->is_closed = 1;
	data->map_name = argv[1];
	data->map_tab = NULL;
	data->map_fd = -1;
	data->mlx_ptr = mlx_init();
	if(!data->mlx_ptr)
	{
		ft_putstr_fd(MLX_ERROR, 2);
		exit (1);
	}
	while (i < 6)
		data->index_checker[i++] = 0;
	i = 0;
	while (i < 4)
		data->img_ptr[i++] = NULL;
	data->map_height = 0;
	data->start_w = 0;
	data->end_w = 0;
	data->labels = ft_split("NO,SO,WE,EA,F,C", ',');
	if (!data->labels)
		exit_parse(data, MEM_ERROR);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_putstr_fd(ARG_ERROR, 2), 1);
	if (!ft_check_extension(argv[1]))
		return (ft_putstr_fd(EXT_ERROR, 2), 1);
	init_data(&data, argv);
	check_map(&data, check_labels, 1, LABEL_ERROR);
	check_map(&data, check_map_height, 1, MAP_ERROR);
	check_map(&data, set_start_width, 1, "");
	check_map(&data, set_end_width, 1, "");
	data.map_tab = init_map_tab(&data);
	check_map(&data, get_next_to_map, 1, "");
	check_map(&data, check_map_close, 0, CLOSED_ERROR);
	for (size_t i = 0; data.map_tab[i]; i++)
		printf("%s|%zu\n", data.map_tab[i], i);
	printf("F %i,%i,%i\n", data.colors[0][0], data.colors[0][1], data.colors[0][2]);
	printf("C %i,%i,%i\n", data.colors[1][0], data.colors[1][1], data.colors[1][2]);
	exit_all(&data, 0);
	return (0);
}
