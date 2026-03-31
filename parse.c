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

void	check_map_space(int fd)
{
	int		map_height;
	char	*str;

	str= NULL;
	map_height = 0;
	while ((str = get_next_line(fd)))
	{
		if (ft_isemptyorspace(str))
		{
			close(fd);
			free(str);
			exit_error("new line in the map error");
		}
		map_height++;
		ft_putstr_fd(str, 1);
		free(str);
	}
	printf("map_height = %i\n", map_height);
}

void	check_element_space(int fd)
{
	int		readed_line;
	char	*str;

	str= NULL;
	readed_line = 0;
	while ((str = get_next_line(fd)) && readed_line != 6)
	{
		if (ft_countword_new(str, "\t\v\f\r ") == 2 && !ft_isemptyorspace(str) && readed_line < 6)
			readed_line++;
		else if((ft_countword_new(str, "\t\v\f\r ") != 2 && !ft_isemptyorspace(str) && readed_line < 6)
		|| (ft_strlen(str) > 1 && ft_isemptyorspace(str) && readed_line < 6))
		{
			close(fd);
			free(str);
			exit_error("map format error");
		}
		free(str);
	}
	printf("readed_line = %i\n", readed_line);
	check_map_space(fd);
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		exit_error("arguments error");
	if (!ft_check_extension(argv[1]))
		exit_error("map extension error");
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		ft_putendl_fd("Error", 2);
		perror("");
		exit(1);
	}
	check_element_space(fd);
	close(fd);
	return (0);
}
