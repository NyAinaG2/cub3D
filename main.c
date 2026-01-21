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
	int sx;
	int sy;
	int e2;

	error = abs(x1 - x0) - abs(y1 - y0);
	x = x0;
	y = y0;
	if (!(sx = x0 < x1))
		sx = -1;
	if (!(sy = y0 < y1))
		sy = -1;
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

void	draw_square(t_mlx *mlx, int x, int y, int w)
{
	int	j;
	int	x0;

	j = 0;
	x0 = 0;
	while(x0 < w)
	{
		j = 0;
		while (j < w)
			img_put_color(mlx, x0 + x - (w / 2), j++ + y - (w / 2), ft_rgb(255, 255 ,255));
		x0++;
	}
}

void	ft_draw_map(t_mlx *mlx)
{
	int	i;
	int	j;
	int	unit;
	int	**map;

	i = 0;
	j = 0;
	unit = mlx->size / 5;
	map = mlx->map;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			if (map[i][j] == 1)
				draw_square(mlx, i * unit + (unit / 2), j * unit + (unit / 2), unit);
			j++;
		}
		i++;
	}
}

void	ft_draw(t_mlx *mlx)
{
	ft_draw_map(mlx);
	draw_line(mlx, 0, 0, 500, 500);
	draw_line(mlx, 0, 500, 500, 0);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}

void	init_mlx(void)
{
	int	map[5][5] =
	{
		{1,1,1,1,1},
		{1,0,0,0,1},
		{1,0,1,0,1},
		{1,0,0,0,1},
		{1,1,1,1,1}
	};
	t_mlx	mlx;

	mlx.map = &map;
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
