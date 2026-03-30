#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

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

void	extract_map(int fd)
{
	char	*str;
	char	**tab;
	int		i;

	str= NULL;
	tab = NULL;
	while ((str = get_next_line(fd)))
	{
		i = 0;
		tab = ft_split_new(str, " 	");
		while (tab[i])
		{
			ft_putendl_fd(tab[i], 1);
			free(tab[i++]);
		}
		free(tab[i]);
		free(tab);
		free(str);
	}
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
	extract_map(fd);
	close(fd);
	return (0);
}
