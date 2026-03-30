/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:05:55 by andrrand          #+#    #+#             */
/*   Updated: 2025/04/04 11:22:52 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_setdata(char *data, char *buff, int r)
{
	size_t	i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (r == 0)
		return (data);
	tmp = malloc(sizeof (char) * (ft_strlen(data) + r + 1));
	if (!tmp)
		return (data);
	while (i < ft_strlen(data))
	{
		tmp[i] = (data)[i];
		i++;
	}
	while (j < r)
		tmp[i++] = buff[j++];
	tmp[i] = 0;
	free(data);
	return (tmp);
}

static char	*ft_read(char *data, int fd)
{
	int		r;
	char	*buff;

	buff = malloc(sizeof (char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	r = read(fd, buff, BUFFER_SIZE);
	if (r < 0 || (!data && r == 0))
	{
		free(data);
		free(buff);
		return (NULL);
	}
	buff[r] = 0;
	data = ft_setdata(data, buff, r);
	free(buff);
	if (!ft_strchr(data, '\n') && r != 0)
		return (ft_read(data, fd));
	return (data);
}

static char	*ft_newdata(char *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (!data[i])
	{
		free(data);
		return (NULL);
	}
	while (data[i] != '\n' && data[i])
		i++;
	if (data[i] == '\n')
	{
		tmp = ft_strdup(data + i + 1);
		free(data);
		return (tmp);
	}
	free(data);
	return (NULL);
}

static char	*ft_newline(char *data)
{
	int	i;

	i = 0;
	while (data[i] != '\n' && data[i])
		i++;
	return (ft_strcpy(data, i + 1));
}

char	*get_next_line(int fd)
{
	static char		*data;
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	data = ft_read(data, fd);
	if (!data)
		return (NULL);
	line = ft_newline(data);
	data = ft_newdata(data);
	return (line);
}
