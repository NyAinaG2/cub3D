#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
// # include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <string.h>
# include <math.h>
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define PI 3.14
# define SPEED 5
# define TEX_LABELS_STATIC ((char *[]){"NO","SO","WE","EA","F","C", NULL})
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
	char		cap;
	int			map_fd;
	int			index_checker[6];
	int			floor_color[3];
	int			ceil_color[3];
	char		*map_name;
	size_t		map_height;
	size_t		start_width;
	size_t		end_width;
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
