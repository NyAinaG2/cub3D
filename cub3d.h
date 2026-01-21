#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <string.h>

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_mlx
{
	void			*map;
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

#endif
