/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 08:37:02 by andrrand          #+#    #+#             */
/*   Updated: 2026/05/08 10:39:59 by andrrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# define MLX_ERROR "Error\nMinilibix Init fail\n"
# define MEM_ERROR "Error\nMemory allocation fail\n"
# define FD_ERROR "Error\nFail to open the map file\n"
# define MAP_ERROR "Error\nSomething is wrong in the map\n"
# define CLOSED_ERROR "Error\nMap is not closed\n"
# define LABEL_ERROR "Error\nWrong map parameters\n"
# define ARG_ERROR "Error\nArgument error\n"
# define EXT_ERROR "Error\nExtention error\n"

typedef struct s_data
{
	int			is_closed;
	void		*img_ptr[4];
	int			img_size[4][2];
	char		**labels;
	char		cap;
	int			map_fd;
	int			index_checker[6];
	int			colors[2][3];
	char		*map_name;
	char		**map_tab;
	size_t		map_height;
	size_t		start_w;
	size_t		end_w;
	void		*mlx_ptr;
}	t_data;

//parse utils
void	trim_newline(char *str);
int		is_allcharin(const char *source, const char *str);
int		ft_isemptyline(const char *str);
int		ft_check_head(char *src, char *str);
size_t	ft_count_char(const char *str, char c);
//parse exit utils
void	free_strs(char **strs);
void	exit_all(t_data *data, int value);
void	exit_parse(t_data *data, char *msg);
//parse check utils
int		ft_check_extension(char *str);
void	check_map(t_data *data, int (*f)(t_data *), int o, char *msg);
void	skip_labels(t_data *data);
int		invalid_color_format(char *str);
//parse check params
int		check_params(t_data *data);
//parse map close
int		check_map_close(t_data *data);
//parse map height
int		check_map_height(t_data *data);
//parese width
int		set_start_width(t_data *data);
int		set_end_width(t_data *data);
//parse_get_next_map
char	**init_map_tab(t_data *data);
int		get_next_to_map(t_data *data);
//parse
void	parse(t_data *data, char **argv);
#endif
