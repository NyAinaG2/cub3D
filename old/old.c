void	draw_player(t_test *data)
{
	t_point	p0;
	t_point	p1;
	t_point	p2;
	t_point	c;

	set_center(data, &c);
	p0.x = c.x + data->playerR * cos(data->direction);
	p0.y = c.y + data->playerR * sin(data->direction);
	p1.x = c.x + data->playerR * cos(data->direction + 2.44);
	p1.y = c.y + data->playerR * sin(data->direction + 2.44);
	p2.x = c.x + data->playerR * cos(data->direction + 3.84);
	p2.y = c.y + data->playerR * sin(data->direction + 3.84);
	draw_line_dda(data, p0, p1, 0xFFFFFF);
	draw_line_dda(data, p0, p2, 0xFFFFFF);
	draw_line_dda(data, p1, p2, 0xFFFFFF);
}

void	draw_rectangle(t_test *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->tile_size)
	{
		j = 0;
		while (j < data->tile_size)
		{
			put_pixel_to_img(data, x * data->tile_size + i, y * data->tile_size
				+ j, color);
			j++;
		}
		i++;
	}
}

void	draw_line_dda(t_test *data, t_point p0, t_point p1, int color)
{
	t_point	delta;
	t_point	inc;
	float	steps;
	int		i;

	delta.x = p1.x - p0.x;
	delta.y = p1.y - p0.y;
	if (fabs(delta.x) > fabs(delta.y))
		steps = fabs(delta.x);
	else
		steps = fabs(delta.y);
	inc.x = delta.x / steps;
	inc.y = delta.y / steps;
	i = 0;
	while (i <= (int)steps)
	{
		put_pixel_to_img(data, (int)p0.x, (int)p0.y, color);
		p0.x += inc.x;
		p0.y += inc.y;
		i++;
	}
}

void	draw_ray(t_test *data)
{
	t_point	p0;
	t_point	p1;
	float	tmp;

	data->fovMin = data->direction - (data->fov / 2);
	data->fovMax = data->direction + (data->fov / 2);
	tmp = data->fovMin;
	while (tmp < data->fovMax)
	{
		p0.x = data->playerX + 0.2 * cos(data->direction);
		p0.y = data->playerY + 0.2 * sin(data->direction);
		tmp = dda(p0, tmp);
		p0.x = p0.x * data->tile_size;
		p0.y = p0.y * data->tile_size;
		p1.x = p1.x * data->tile_size;
		p1.y = p1.y * data->tile_size;
		draw_line_dda(data, p0, p1, 0x555555);
		tmp += data->step;
	}
}
