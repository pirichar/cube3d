#include "../include/cub3d.h"


//https://harm-smits.github.io/42docs/libs/minilibx/images.html



int	keypress(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
	{
		printf(GRN"Good bye!\n"RESET);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit (0);
	}	

	if (key == KEY_M)
	{
		void	*img;
		int		img_width;
		int		img_height;

		img = NULL;
		mlx->imgu = mlx_xpm_file_to_image(mlx->mlx_ptr, "./boyo.xpm", &img_width, &img_height);
		if (mlx->imgu == NULL)
		{
			printf(RED"COULD'T READ THE IMAGE\n"RESET);
			return 1;
		}
		else
			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
							mlx->imgu, 0 , 0 );
		
		printf("SHOULD BE DONE\n");
	}	
	return (0);
}

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
	int ret;
	(void)argv;

	if (argc == 2)
	{
		
		init_mlx(&mlx);
		//open map
		mlx.fd = open(argv[1], O_RDONLY);
		if (mlx.fd == -1)
		{
			perror("open");
			return (1);
		}
		ret = read(mlx.fd, mlx.buffer, 4000);
		mlx.map = ft_split(mlx.buffer, '\n');
		for(int i = 0; mlx.map[i]; i++)
			printf("%s\n", mlx.map[i]);
		//parse map

		//print map and player with position

		//struct player with enum position
		mlx_key_hook(mlx.win_ptr, keypress, &mlx);
		mlx_loop(mlx.mlx_ptr);
	}
	else {
		printf("Please provide a map to the program\n");
	}

}

