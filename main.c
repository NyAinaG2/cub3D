#include "cub3d.h"

int	ft_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	img_put_color(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	on_close(t_mlx *param)
{
	mlx_destroy_image(param->mlx_ptr, param->img_ptr);
	mlx_clear_window(param->mlx_ptr, param->win_ptr);
	mlx_destroy_window(param->mlx_ptr, param->win_ptr);
	mlx_destroy_display(param->mlx_ptr);
	free(param->mlx_ptr);
	exit(0);
	return (0);
}

int	key_hook(int key, t_mlx *param)
{
	if (key == 65307)
		on_close(param);
	return (0);
}

void	ft_draw(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < mlx->size)
	{
		y = 0;
		while (y < mlx->size)
		{
			img_put_color(mlx, x, y, ft_rgb(0, 255 ,255));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}

void	init_mlx(void)
{
	t_mlx	mlx;

	mlx.size = 500;
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.size, mlx.size, "Fract'ol");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, mlx.size, mlx.size);
	mlx.addr = mlx_get_data_addr(mlx.img_ptr, &mlx.bits_per_pixel,
			&mlx.line_length, &mlx.endian);
	ft_draw(&mlx);
	mlx_key_hook(mlx.win_ptr, key_hook, &mlx);
	mlx_hook(mlx.win_ptr, 17, 0, on_close, &mlx);
	mlx_loop(mlx.mlx_ptr);
}

int	main(void)
{
	init_mlx();
	return (0);
}
