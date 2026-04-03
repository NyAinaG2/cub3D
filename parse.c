#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include "cub3d.h"

int		ft_countword_new(char const *s, char *str);

void	exit_error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	exit(1);
}

int	ft_check_extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 4)
		return (0);
	return (ft_strncmp(str + (len - 4),".map", 4) == 0);
}

int	ft_isnothing(const char *str)
{
	if(!str || !*str)
		return (1);
	while (*str)
	{
		if (!ft_strchr(" ", *str++))
			return (0);
	}
	return (1);
}

int	check_element_space(t_data *data)
{
	int		readed_line;
	char	*str;

	str= NULL;
	readed_line = 0;
	while (readed_line != 6)
	{
		str = get_next_line(data->map_fd);
		if (ft_countword_new(str, "\t\v\f\r ") == 2 && !ft_isnothing(str) && readed_line < 6)
			readed_line++;
		else if((ft_countword_new(str, "\t\v\f\r ") != 2 && !ft_isnothing(str) && readed_line < 6)
		|| (ft_strlen(str) > 1 && ft_isnothing(str) && readed_line < 6) || !str)
		{
			free(str);
			return (0);
		}
		free(str);
	}
	return (readed_line == 6);
}

int	get_map_height(t_data *data, int begin)
{
	char	*str;

	str = get_next_line(data->map_fd);
	if (begin == 0)
		check_element_space(data);
	if (!str)
	{
		free(str);
		return (0);
	}
	if (ft_isnothing(str) && ft_strlen(str) > 1)
	{
		free(str);
		return (-begin);
	}
	if (ft_isnothing(str))
	{
		free(str);
		if (begin > 0)
			return (-begin);
		return (get_map_height(data, 0));
	}
	free(str);
	return (1 + get_map_height(data, ++begin));
}

int	check_map_height(t_data *data)
{
	return ((data->map_height = get_map_height(data, 0)) > 2);
}

void	check_map(t_data *data, int (*f)(t_data *data))
{
	if((data->map_fd = open(data->map_name, O_RDONLY)) < 0)
	{
		ft_putendl_fd("Error", 2);
		perror("");
		exit(1);
	}
	if (!f(data))
	{
		purge_get_next_line(data->map_fd);
		close(data->map_fd);
		exit_error("Map format error");
	}
	purge_get_next_line(data->map_fd);
	close(data->map_fd);
}

void	fill_fd_texture(int	*fd, char *str)
{
	int	tmp;

	if ((tmp = open(str, O_RDONLY)) < 0)
	{
		*fd = -1;
		return ;
	}
	close(tmp);
	if (*fd == -1)
		*fd = 0;
	else
		*fd = -1;
}

void	check_texture(t_data *data, char *str)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(str, ' ');
	if (ft_strncmp("NO", tab[0], ft_strlen(tab[0])) == 0)
		fill_fd_texture(&data->textures_fd[0], tab[0]);
	if (ft_strncmp("SO", tab[0], ft_strlen(tab[0]))  == 0)
		fill_fd_texture(&data->textures_fd[1], tab[0]);
	if (ft_strncmp("WE", tab[0], ft_strlen(tab[0]))  == 0)
		fill_fd_texture(&data->textures_fd[2], tab[0]);
	if (ft_strncmp("EA", tab[0], ft_strlen(tab[0]))  == 0)
		fill_fd_texture(&data->textures_fd[3], tab[0]);
	while (tab[i])
		free(tab[i++]);
	free(tab[i]);
	free(tab);
}


int	check_map_texture(t_data *data)
{
	int		readed_line;
	char	*str;
	int		i;

	str= NULL;
	readed_line = 0;
	i = 0;
	while (readed_line != 6)
	{
		str = get_next_line(data->map_fd);
		if (ft_countword_new(str, " ") == 2 && !ft_isnothing(str) && readed_line < 4)
		{
			check_texture(data, str);
			readed_line++;
		}
		free(str);
	}
	while (i < 4)
	{
		if (data->textures_fd[i])
			close(data->textures_fd[i]);
		i++;
	}
	return (readed_line == 6);
}

void	init_data(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->cap = 0;
	data->map_name = argv[1];
	data->map_fd = -1;
	while (i < 4)
		data->textures_fd[i++] = -1;
	data->map_height = 0;
	data->map_width = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data, argv);
	if (argc != 2)
		exit_error("arguments error");
	if (!ft_check_extension(argv[1]))
		exit_error("map extension error");
	check_map(&data, check_element_space);
	check_map(&data, check_map_height);
	check_map(&data, check_map_texture);
	return (0);
}
