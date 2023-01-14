#include "../include/cub3d.h"


//https://harm-smits.github.io/42docs/libs/minilibx/images.html

void	redraw_map(t_mlx *mlx)
{
		for(int i = 0; mlx->map[i]; i++)
	{
		mlx->y = 100 * i;
		for (int j = 0;mlx->map[i][j];j++)
		{
			mlx->x = 100 * j;
			if (mlx->map[i][j] == '1')
			{
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
						mlx->image.wall, mlx->x , mlx->y );
			}
			if (mlx->map[i][j] == '0')
			{
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
						mlx->image.floor, mlx->x , mlx->y );
			}
			if (mlx->map[i][j] == 'N')
			{
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
						mlx->image.floor, mlx->x, mlx->y);
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
						mlx->image.player, mlx->x, mlx->y);
			}
		}
	}
}

int	keypress(int key, t_mlx *mlx)
{
    if (key == KEY_ESC)
    {
        printf(GRN"Good bye!\n"RESET);
        mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
        exit (0);
    }
    if (key == KEY_D)
    {
        if (mlx->map[mlx->player_y][mlx->player_x + 1] != '1')
        {
            mlx->map[mlx->player_y][mlx->player_x] = '0';
            mlx->player_x++;
            mlx->map[mlx->player_y][mlx->player_x] = 'N';
            mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		}
	}
	if (key == KEY_W)
    {
        if (mlx->map[mlx->player_y - 1][mlx->player_x] != '1')
        {
            mlx->map[mlx->player_y][mlx->player_x] = '0';
            mlx->player_y--;
            mlx->map[mlx->player_y][mlx->player_x] = 'N';
            mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		}
	}
	if (key == KEY_A)
    {
        if (mlx->map[mlx->player_y][mlx->player_x - 1] != '1')
        {
            mlx->map[mlx->player_y][mlx->player_x] = '0';
            mlx->player_x--;
            mlx->map[mlx->player_y][mlx->player_x] = 'N';
            mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		}
	}
	if (key == KEY_S)
    {
        if (mlx->map[mlx->player_y + 1][mlx->player_x] != '1')
        {
            mlx->map[mlx->player_y][mlx->player_x] = '0';
            mlx->player_y++;
            mlx->map[mlx->player_y][mlx->player_x] = 'N';
            mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		}
	}
	redraw_map(mlx);

	return 0;
}

void	init_mlx(t_mlx *mlx)
{
	mlx->win_x = mlx->map_lenght*100;
	mlx->win_y = mlx->map_height*100;
	mlx->mouse.move = 0;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->win_x,
			mlx->win_y, "Cub3d");
	mlx->image.wall = mlx_xpm_file_to_image(mlx->mlx_ptr, "./images/wall.xpm", &mlx->image.width, &mlx->image.height);
	mlx->image.floor = mlx_xpm_file_to_image(mlx->mlx_ptr, "./images/floor.xpm", &mlx->image.width, &mlx->image.height);
	mlx->image.player = mlx_xpm_file_to_image(mlx->mlx_ptr, "./images/boyo.xpm", &mlx->image.width, &mlx->image.height);

}

void	initialize_first_map(t_mlx *mlx)
{
	for(int i = 0; mlx->map[i]; i++)
	{
		mlx->y = 100 * i;
		for (int j = 0;mlx->map[i][j];j++)
		{	
			mlx->x = 100 * j;
			if (mlx->map[i][j] == '1')
			{
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
						mlx->image.wall, mlx->x , mlx->y );
			}
			if (mlx->map[i][j] == '0')
			{
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
						mlx->image.floor, mlx->x , mlx->y );
			}
			if (mlx->map[i][j] == 'N')
			{
				//prendre en note les coordonnées du joueur
				mlx->player_x = j;
				mlx->player_y = i;
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
						mlx->image.floor, mlx->x , mlx->y );
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
						mlx->image.player, mlx->x , mlx->y );
			}
			printf("%c",mlx->map[i][j]);
		}
		printf("\n");
	}
}

int	main(int argc, char **argv)
{

	t_mlx mlx;
	(void)argv;

	if (argc == 2)
	{
		//open map
		mlx.fd = open(argv[1], O_RDONLY);
		if (mlx.fd == -1)
		{
			perror("open");
			return (1);
		}
		//parse map
		mlx.ret = read(mlx.fd, mlx.buffer, 4000);
		mlx.map = ft_split(mlx.buffer, '\n');
		for(int i = 0; mlx.map[i]; i++)
			mlx.map_height = i + 1;
		for(int j = 0;mlx.map[0][j];j++)
			mlx.map_lenght = j + 1;

		//Initialize map
		init_mlx(&mlx);

		//initialiser la map la premiere fois 
		initialize_first_map(&mlx);
		mlx_key_hook(mlx.win_ptr, keypress, &mlx);
		mlx_loop(mlx.mlx_ptr);
	}
	else {
		printf("Please provide a map to the program\n");
	}

}

