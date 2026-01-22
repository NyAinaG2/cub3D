#include "cub3d.h"

void	ft_draw(t_mlx *mlx);

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
		{1, 0, 2, 0, 1},
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

int	key_hook(int key, t_mlx *mlx)
{
	if (key == KEY_W)
		mlx->player_pos.y -= mlx->speed;
	if (key == KEY_A)
		mlx->player_pos.x -= mlx->speed;
	if (key == KEY_S)
		mlx->player_pos.y += mlx->speed;
	if (key == KEY_D)
		mlx->player_pos.x += mlx->speed;
	if (key == 65307)
		on_close(mlx);
	if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		ft_draw(mlx);
	return (0);
}

void	draw_line(t_mlx *mlx, t_vector p0, t_vector p1, int color)
{

	int error;
	int x;
	int y;
	int sx;
	int sy;
	int e2;

	error = abs(p1.x - p0.x) - abs(p1.y - p0.y);
	x = p0.x;
	y = p0.y;
	if (!(sx = p0.x < p1.x))
		sx = -1;
	if (!(sy = p0.y < p1.y))
		sy = -1;
	while (1)
	{
		img_put_color(mlx, x, y, color);
		if (x == p1.x && y == p1.y)
			break;
		e2 = 2 * error;
		if (e2 > -abs(p1.y - p0.y))
		{
			error -= abs(p1.y - p0.y);
			x += sx;
		}
		if (e2 < abs(p1.x - p0.x))
		{
			error += abs(p1.x - p0.x);
			y += sy;
		}
	}
}

void	draw_square(t_mlx *mlx, t_vector pos, int w, int color)
{
	int	j;
	int	x0;

	j = 0;
	x0 = 0;
	while(x0 < w)
	{
		j = 0;
		while (j < w)
			img_put_color(mlx, x0 + pos.x - (w / 2), j++ + pos.y - (w / 2), color);
		x0++;
	}
}

void	ft_draw_map(t_mlx *mlx)
{
	int			i;
	int			j;
	int			unit;
	t_vector	tmp;

	i = 0;
	j = 0;
	unit = mlx->scale;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			tmp.x = i * unit + (unit / 2);
			tmp.y = j * unit + (unit / 2);
			if (mlx->map[j][i] == 1)
				draw_square(mlx, tmp, unit, ft_rgb(255,255,255));
			else
				draw_square(mlx, tmp, unit, ft_rgb(0,0,0));
			j++;
		}
		i++;
	}
}

void	ft_draw(t_mlx *mlx)
{
	ft_draw_map(mlx);
	draw_square(mlx, mlx->player_pos, 10, ft_rgb(0, 50 , 150));
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}

void	init_player_position(t_mlx *mlx)
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
			if (mlx->map[j][i] == 2)
			{
				mlx->player_pos.x = i * unit + (unit / 2);
				mlx->player_pos.y = j * unit + (unit / 2);
				mlx->player_pos.z = 0;
			}
			j++;
		}
		i++;
	}
}

void	init_mlx(void)
{
	t_mlx	mlx;

	mlx.size = 500;
	mlx.speed = 5;
	mlx.scale = mlx.size / 5;
	mlx.map = ft_allocate_map();
	init_player_position(&mlx);
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.size, mlx.size, "cub3D");
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
