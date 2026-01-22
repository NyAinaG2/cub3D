#include "cub3d.h"

void	ft_free_map(t_mlx *mlx)
{
	int	i;

	if (!mlx->map)
		return ;
	i = 0;
	while (i < 5)
	{
		if (mlx->map[i])
			free(mlx->map[i]);
		i++;
	}
	if (mlx->map)
		free(mlx->map);
}

int	**ft_allocate_map(void)
{
	int	temp[5][5] = {
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1}
	};
	int	**map;
	int	i;
	int	j;

	map = (int **)malloc(sizeof(int *) * 5);
	if (!map)
		return (NULL);
	i = 0;
	while (i < 5)
	{
		map[i] = (int *)malloc(sizeof(int) * 5);
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return (NULL);
		}
		j = 0;
		while (j < 5)
		{
			map[i][j] = temp[i][j];
			j++;
		}
		i++;
	}
	return (map);
}

int	on_close(t_mlx *param)
{
	mlx_destroy_image(param->mlx_ptr, param->img_ptr);
	mlx_clear_window(param->mlx_ptr, param->win_ptr);
	mlx_destroy_window(param->mlx_ptr, param->win_ptr);
	mlx_destroy_display(param->mlx_ptr);
	free(param->mlx_ptr);
	ft_free_map(param);
	exit(0);
	return (0);
}

int	key_hook(int key, t_mlx *param)
{

	if (key == KEY_W)
		printf("KEY_W\n");
	if (key == KEY_A)
		printf("KEY_A\n");
	if (key == KEY_S)
		printf("KEY_S\n");
	if (key == KEY_D)
		printf("KEY_D\n");
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

	i = 0;
	j = 0;
	unit = mlx->size / 5;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			if (mlx->map[i][j] == 1)
				draw_square(mlx, i * unit + (unit / 2), j * unit + (unit / 2), unit);
			j++;
		}
		i++;
	}
}

void	ft_draw_grid(t_mlx *mlx)
{
	int	j;
	int	unit;

	j = 0;
	unit = mlx->size / 5;
	while (j < 5)
	{
		draw_line(mlx, 0, j * unit, 500, j * unit);
		draw_line(mlx, j * unit, 0, j * unit, 500);
		j++;
	}
}

// void	put_play(t_mlx *mlx)
// {

// }

void	ft_draw(t_mlx *mlx)
{
	ft_draw_map(mlx);
	ft_draw_grid(mlx);
	draw_line(mlx, 0, 0, 500, 500);
	draw_line(mlx, 0, 500, 500, 0);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}

void	init_mlx(void)
{
	t_mlx	mlx;

	mlx.map = ft_allocate_map();
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
