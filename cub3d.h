#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include <stdlib.h>

typedef struct s_mlx
{
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
