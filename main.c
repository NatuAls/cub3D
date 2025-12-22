#include <mlx.h>
#include <math.h>

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_img;

typedef	struct	s_player 
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	a;
	int	up_pressed;
	int	l_pressed;
	int	r_pressed;
	int	dn_pressed;
}		t_player;

typedef struct	s_game 
{
	void		*mlx;
	void		*mlx_win;
	t_player	player;
	t_img		img;
}		t_game;

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_img *img, int x, int y, int size, int color)
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

void	draw_background_map(t_img *img)
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

void	draw_line(t_img *img, double beginx, double beginy, double endx, double endy)
{
	double	dx = endx - beginx;
	double	dy = endy - beginy;
	double	steps;
	double	x_inc;
	double	y_inc;
	int	i = 0;
	double	x = beginx;
	double	y = beginy;

	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	while (i < steps)
	{
		my_mlx_pixel_put(img, (int)x, (int)y, 0x00FF0000);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

void	draw_player(t_game *game)
{
	int	endx;
	int	endy;

	endx = game->player.x + game->player.dx * 30;
	endy = game->player.y + game->player.dy * 30;
	draw_square(&game->img, game->player.x, game->player.y, 8, 0x00FF0000);
	draw_line(&game->img, game->player.x, game->player.y, endx, endy);
}

void	draw_map(t_img *img)
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
	if (key_code == 65362) // up
		game->player.up_pressed = 1;
	if (key_code == 65361) // <-
		game->player.l_pressed = 1;
	if (key_code == 65364) //down
		game->player.dn_pressed = 1;
	if (key_code == 65363) // ->
		game->player.r_pressed = 1;
	return 0;
}

int	key_release(int key_code, t_game *game)
{
	if (key_code == 65362) // up
		game->player.up_pressed = 0;
	if (key_code == 65361) // <-
		game->player.l_pressed = 0;
	if (key_code == 65364) //down
		game->player.dn_pressed = 0;
	if (key_code == 65363) // ->
		game->player.r_pressed = 0;
	return 0;
}

int	move_player(t_game *game)
{
	double	mov_speed;
	double	rot_speed;
	
	mov_speed = 0.5;
	rot_speed = 0.00999;
	if (game->player.up_pressed) // up
	{
		game->player.x += game->player.dx * mov_speed;
		game->player.y += game->player.dy * mov_speed;
	}
	if (game->player.l_pressed) // <-
	{
		game->player.a -= rot_speed;
		game->player.dx = cos(game->player.a);
		game->player.dy = sin(game->player.a);
	}
	if (game->player.dn_pressed) //down
	{
		game->player.x -= game->player.dx * mov_speed;
		game->player.y -= game->player.dy * mov_speed;
	}
	if (game->player.r_pressed) // ->
	{
		game->player.a += rot_speed;
		game->player.dx = cos(game->player.a);
		game->player.dy = sin(game->player.a);
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
	game.player.x = 300;
	game.player.y = 300;
	game.player.a = 3 * M_PI_2;
	game.player.dx = cos(game.player.a);
	game.player.dy = sin(game.player.a);
	game.player.up_pressed = 0;
	game.player.l_pressed = 0;
	game.player.r_pressed = 0;
	game.player.dn_pressed = 0;
	draw_map(&game.img);
	draw_player(&game);
	mlx_put_image_to_window(game.mlx, game.mlx_win, game.img.img, 0, 0);
	mlx_hook(game.mlx_win, 2, 1, key_press, &game);
	mlx_hook(game.mlx_win, 3, 2, key_release, &game);
	mlx_loop_hook(game.mlx, move_player, &game);
	mlx_loop(game.mlx);
	return (0);
}
