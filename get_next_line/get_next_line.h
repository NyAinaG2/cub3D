/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:06:03 by andrrand          #+#    #+#             */
/*   Updated: 2026/04/03 08:37:54 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1

# include "../libft/libft.h"

char	*ft_strcpy(char *src, size_t len);
void	purge_get_next_line(int fd);
char	*get_next_line(int fd);

#endif
