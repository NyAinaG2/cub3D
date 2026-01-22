#include "cub3d.h"

int	ft_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	img_put_color(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > mlx->size || y < 0 || y > mlx->size)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}
