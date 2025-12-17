#include <mlx.h>
#include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct	s_game 
{
	void	*mlx;
	void	*mlx_win;
	double	px;
	double	py;
	double	pdx;
	double	pdy;
	double	pa;
	t_data	img;
}		t_game;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_data *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

int	mapX=8, mapY=8, mapS=64;
int	map[] =
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

void	draw_background_map(t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < mapY)
	{
		j = 0;
		while (j < mapX)
		{
			draw_square(img, j *mapS, i * mapS, mapS, 0x00000000);
			j++;
		}
		i++;
	}
}

void	draw_line(t_data *img, double beginx, double beginy, double endx, double endy)
{
	double	dx = endx - beginx;
	double	dy = endy - beginy;
	double	steps;	

	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);

	while (1)
	{
		if (beginx == endx && beginy == endy)
			break;
		my_mlx_pixel_put(img, beginx, beginy, 0x00FF0000);
		if (beginx != endx)
			beginx++;
		if (beginy != endy)
			beginy++;
	}
}

void	draw_player(t_game *game)
{
	int	endx;
	int	endy;

	endx = game->px + game->pdx * 50;
	endy = game->py + game->pdy * 50;
	draw_square(&game->img, game->px, game->py, 8, 0x00FF0000);
	//draw_line(&game->img, game->px, game->py, endx, endy);
}

void	draw_map(t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < mapY)
	{
		j = 0;
		while (j < mapX)
		{
			if (map[i * mapX + j] == 1)
				draw_square(img, j * mapS, i * mapS, mapS - 1, 0x00808080);
			else
				draw_square(img, j *mapS, i * mapS, mapS - 1, 0x00FFFFFF);
			j++;
		}
		i++;
	}
}

int	key_press(int key_code, t_game *game)
{
	double	mov_speed;
	double	rot_speed;
	
	mov_speed = 5.0;
	rot_speed = 0.5;
	if (key_code == 65362) // up
	{
		game->px += game->pdx * mov_speed;
		game->py += game->pdy * mov_speed;
	}
	if (key_code == 65361) // <-
	{
		game->pa -= rot_speed;
		game->pdx = cos(game->pa);
		game->pdy = sin(game->pa);
	}
	if (key_code == 65364) //down
	{
		game->px -= game->pdx * mov_speed;
		game->py -= game->pdy * mov_speed;
	}
	if (key_code == 65363) // ->
	{
		game->pa += rot_speed;
		game->pdx = cos(game->pa);
		game->pdy = sin(game->pa);
	}
	draw_background_map(&game->img);
	draw_map(&game->img);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	t_game		game;

	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, 1920, 1080, "cub3d");
	game.img.img = mlx_new_image(game.mlx, 1920, 1080);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);
	game.px = 300;
	game.py = 300;
	game.pa = 3 * M_PI_2;
	game.pdx = cos(game.pa);
	game.pdy = sin(game.pa);
	draw_map(&game.img);
	draw_player(&game);
	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img.img, 0, 0);
	mlx_key_hook(game.mlx_win, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
