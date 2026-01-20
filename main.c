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

void	draw_line(t_mlx *mlx, int x0, int y0, int x1, int y1)
{

	int error;
	int x;
	int y;
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int e2;

	error = abs(x1 - x0) - abs(y1 - y0);
	x = x0;
	y = y0;
	while (1)
	{
		img_put_color(mlx, x, y, ft_rgb(255, 255 ,255));
		if (x == x1 && y == y1)
			break;
		e2 = 2 * error;
		if (e2 > -abs(y1 - y0))
		{
			error -= abs(y1 - y0);
			x += sx;
		}
		if (e2 < abs(x1 - x0))
		{
			error += abs(x1 - x0);
			y += sy;
		}
	}
}

void	ft_draw(t_mlx *mlx)
{
	draw_line(mlx, 0, 0, 0, 200);
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
