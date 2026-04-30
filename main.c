#include "cub3d.h"

int main()
{
	t_test data;

	if (init(&data)) printf("OK\n");
	mlx_loop(data.mlx_ptr);
	return (0);
}
