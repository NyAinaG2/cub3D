#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
// # include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <string.h>
# include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"


# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define PI 3.14
# define SPEED 5
# define MEM_ERROR "Error\nMemory allocation fail\n"
# define FD_ERROR "Error\nFail to open the map file\n"
# define MAP_ERROR "Error\nSomething is wrong in the map\n"
# define CLOSED_ERROR "Error\nMap is not closed\n"
# define LABEL_ERROR "Error\nSomething is wrong in the 6 first elements\n"
# define ARG_ERROR "Error\nArgument error\n"
# define EXT_ERROR "Error\nExtention error\n"
typedef struct s_vector
{

	int		x;
	int		y;
	float	dx;
	float	dy;
	float	z;
}	t_vector;

typedef struct s_data
{
	char		**labels;
	char		cap;
	int			map_fd;
	int			index_checker[6];
	int			floor_color[3];
	int			ceil_color[3];
	char		*map_name;
	char		**map_tab;
	size_t		map_height;
	size_t		start_w;
	size_t		end_w;
}	t_data;

typedef struct s_mlx
{
	int				**map;
	t_vector		player_pos;
	int				scale;
	int				map_width;
	int				map_height;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				size;
}	t_mlx;

int		ft_rgb(int r, int g, int b);
void	img_put_color(t_mlx *mlx, int x, int y, int color);
#endif
