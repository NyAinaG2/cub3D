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
	while (strs[i])
		free(strs[i++]);
	free(strs[i]);
	free(strs);
}

void	exit_error(t_data *data)
{
	free_strs(data->labels);
	ft_putendl_fd("Error", 2);
	perror("");
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
	int	len;

	len = ft_strlen(str);
	if (len < 4)
		return (0);
	return (ft_strncmp(str + (len - 4),".map", 4) == 0);
}

int	ft_isemptyline(const char *str)
{
	return (str && ft_strlen(str) == 1 && *str == '\n');
}



int	check_element_space(t_data *data)
{
	int		line;
	char	*str;

	str= NULL;
	line = 0;
	while (line < 6)
	{
		if (!(str = get_next_line(data->map_fd)))
			break ;
		if (ft_isemptyline(str))
		{
			free(str);
			continue ;
		}
		if (ft_countword(str, ' ') != 2 && line < 6)
		{
			free(str);
			break;
		}
		line++;
		free(str);
	}
	return (line == 6);
}

int	check_map_height(t_data *data)
{
	char	*str;
	int		height;

	height = 0;
	str = NULL;
	check_element_space(data);
	while (1)
	{
		if (!(str = get_next_line(data->map_fd))) break ;
		if (ft_isemptyline(str) && height == 0)
		{
			free(str);
			continue ;
		}
		if ((ft_isemptyline(str) && height > 0)
		|| (!ft_isemptyline(str) && !is_allcharin(str, "10NOWE \n")))
		{
			free(str);
			return (0);
		}
		height++;
		free(str);
	}
	data->map_height = height;
	return (height > 2);
}

void	check_map(t_data *data, int (*f)(t_data *data))
{
	if((data->map_fd = open(data->map_name, O_RDONLY)) < 0)
		exit_error(data);
	if (!f(data))
	{
		purge_get_next_line(data->map_fd);
		close(data->map_fd);
		exit_error(data);
	}
	purge_get_next_line(data->map_fd);
	close(data->map_fd);
}



int	check_fd(char *str)
{
	int	fd;

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
	str[ft_strlen(str) - 1] = 0;
	strs = ft_split(str, ',');
	while (strs[i])
		i++;
	while (strs[j] && i == 3)
	{
		if (ft_atoi(strs[j]) > 255 || ft_atoi(strs[j]) < 0
			|| !is_allcharin(strs[j],"1234567890"))
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
		if (ft_strncmp(data->labels[i], strs[0], ft_strlen(strs[0])) == 0)
		{
			data->index_checker[i]++;
			error = data->index_checker[i] > 1;
			if (i <= 3 && !error)
				error = !check_fd(strs[1]);
			else if (!error)
				error = !check_color(strs[1]);
			break;
		}
		i++;
	}
	error = i >= 6;
	free_strs(strs);
	return (!error);
}

int	check_labels(t_data *data)
{
	int		line;
	char	*str;

	str= NULL;
	line = 0;
	while (line < 6)
	{
		if (!(str = get_next_line(data->map_fd)))
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
			break;
		}
		line++;
		free(str);
	}
	printf("line  = %d\n", line);
	return (line == 6);
}

void	init_data(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->cap = 0;
	data->map_name = argv[1];
	data->map_fd = -1;
	data->labels = ft_split("NO,SO,WE,EA,F,C", ',');
	while (i < 3)
	{
		data->floor_color[i] = 0;
		data->ceil_color[i++] = 0;
	}
	i = 0;
	while (i < 6)
		data->index_checker[i++] = 0;
	data->map_height = 0;
	data->map_width = 0;
}

int	main(int argc, char **argv)
{


	t_data	data;

	init_data(&data, argv);
	if (argc != 2)
		exit_error(&data);
	if (!ft_check_extension(argv[1]))
		exit_error(&data);
	//checking 6 first map element
	check_map(&data, check_labels);
	// check_map(&data, check_map_height);
	// printf("map height = %d\n", data.map_height);
	// check_map(&data, check_element_count);
	return (0);
}
