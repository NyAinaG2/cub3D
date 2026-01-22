#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <string.h>
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_mlx
{
	int				**map;
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
