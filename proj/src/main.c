#include "cub3d.h"

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, EVT_PRESS, 1L << 0, key_press, game);
	mlx_hook(game->win, EVT_RELEASE, 1L << 1, key_release, game);
	mlx_hook(game->win, EVT_DESTROY, 0, close_window, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

static int	init_all(t_game *game)
{
	if (!init_game(game))
		return (0);
	if (!init_hardcoded_map(game))
	{
		free_game(game);
		return (0);
	}
	if (!find_player(game))
	{
		free_game(game);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!validate_args(argc, argv))
		return (1);
	memset(&game, 0, sizeof(t_game));
	if (!parser(&game, argv[1]))
		return (1);
	ft_printf("NO:%s$\n", game.tex.path_no);
	ft_printf("SO:%s$\n", game.tex.path_so);
	ft_printf("WE:%s$\n", game.tex.path_we);
	ft_printf("EA:%s$\n", game.tex.path_ea);
	if (!init_all(&game))
	{
		write(2, "Error\nInitialization failed\n", 28);
		return (1);
	}
	setup_hooks(&game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
