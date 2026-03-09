/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <nalesso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:52:58 by nalesso           #+#    #+#             */
/*   Updated: 2026/02/05 18:22:04 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, EVT_PRESS, 1L << 0, key_press, game);
	mlx_hook(game->win, EVT_RELEASE, 1L << 1, key_release, game);
	mlx_hook(game->win, EVT_DESTROY, 0, close_window, game);
	mlx_hook(game->win, EVT_MOUSE_MOVE, 1L << 6, mouse_move, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

static int	init_all(t_game *game)
{
	if (!init_game(game))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (!validate_args(argc, argv))
		return (1);
	if (!parser(&game, argv[1]))
		return (free_game(&game), 1);
	if (!init_all(&game))
		return (free_game(&game), 1);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
