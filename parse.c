#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

int		ft_countword_new(char const *s, char *str);
char	**ft_split_new(char const *s, char *str);

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

int	ft_isemptyorspace(const char *str)
{
	if(!str || !*str)
		return (1);
	while (*str)
	{
		if (!ft_strchr("\t\v\f\r\n ", *str++))
			return (0);
	}
	return (1);
}

int	ft_isindicator(const char *str)
{
	if(!str || !*str)
		return (0);
	while (*str)
	{
		if (!ft_strchr("\t\v\f\r\n ", *str++))
			return (1);
	}
	return (0);
}

int	skip_emptyline(int fd, int begin)
{
	char	*str;

	str = get_next_line(fd);
	if (!str)
	{
		free(str);
		return (0);
	}
	if (ft_isemptyorspace(str))
	{
		free(str);
		if (begin > 0)
			return (-begin);
		return (skip_emptyline(fd, 0));
	}
	begin++;
	free(str);
	return (1 + skip_emptyline(fd, begin));
}

int	check_map_space(int fd)
{
	int		map_height;
	char	*str;

	str= NULL;
	map_height = 0;
	while ((str = get_next_line(fd)))
	{
		ft_putendl_fd(str, 1);
		if (ft_isemptyorspace(str))
		{
			free(str);
			return (0);
		}
		map_height++;
		free(str);
	}
	if (map_height <= 2)
		return (0);
	printf("map_height = %i\n", map_height);
	return (1);
}

int	check_element_space(int fd)
{
	int		readed_line;
	char	*str;

	str= NULL;
	readed_line = 0;
	while (readed_line != 6)
	{
		str = get_next_line(fd);
		if (ft_countword_new(str, "\t\v\f\r ") == 2 && !ft_isemptyorspace(str) && readed_line < 6)
			readed_line++;
		else if((ft_countword_new(str, "\t\v\f\r ") != 2 && !ft_isemptyorspace(str) && readed_line < 6)
		|| (ft_strlen(str) > 1 && ft_isemptyorspace(str) && readed_line < 6) || !str)
		{
			free(str);
			return (0);
		}
		free(str);
	}
	printf("readed_line = %i\n", readed_line);
	if (readed_line != 6)
		return (0);
	printf("skip_emptyline = %i\n", skip_emptyline(fd, 0));
	return (1);
	// return (check_map_space(fd));
}

void	check_map(char *map, int (*f)(int))
{
	int	fd;

	if((fd = open(map, O_RDONLY)) < 0)
	{
		ft_putendl_fd("Error", 2);
		perror("");
		exit(1);
	}
	if (!f(fd))
	{
		close(fd);
		exit_error("Map format error");
	}
	close(fd);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		exit_error("arguments error");
	if (!ft_check_extension(argv[1]))
		exit_error("map extension error");
	//6 th element
	check_map(argv[1], check_element_space);
	//map data
	return (0);
}
