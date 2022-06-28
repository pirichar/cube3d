#include "../include/cub3d.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->win_x = 1280;
	mlx->win_y = 720;
	mlx->mouse.move = 0;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->win_x,
			mlx->win_y, "Cub3d");
	mlx->img.img = mlx_new_image(mlx->mlx_ptr, mlx->win_x, mlx->win_y);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	mlx->menu_state = 'n';
}

int	main(int argc, char **argv)
{

	t_mlx mlx;
	(void)argv;

	if (argc == 2)
	{
		
		init_mlx(&mlx);
		//open map
		// mlx.fd = open(argv[1], O_RDONLY);

		//parse map

		//print map and player with position
		//struct player with enum position
		mlx_loop(mlx.mlx_ptr);
	}

}

