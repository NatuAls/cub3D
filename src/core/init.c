/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <nalesso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:52:57 by nalesso           #+#    #+#             */
/*   Updated: 2026/02/05 17:20:14 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_keys(t_game *game)
{
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
}

void	init_player_dir(t_player *p, char dir)
{
	if (dir == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (dir == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
}

void	init_player(t_game *game, char dir, double x, double y)
{
	game->player.initialized = 1;
	game->player.pos_x = x;
	game->player.pos_y = y;
	if (dir == 'N' || dir == 'S')
		init_player_dir(&game->player, dir);
	else if (dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

static int	init_mlx_image(t_game *game)
{
	game->frame.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->frame.img)
		return (0);
	game->frame.addr = mlx_get_data_addr(game->frame.img,
			&game->frame.bpp, &game->frame.line_len, &game->frame.endian);
	if (!game->frame.addr)
		return (0);
	game->frame.width = WIN_WIDTH;
	game->frame.height = WIN_HEIGHT;
	return (1);
}

int	init_game(t_game *game)
{
	game->last_mouse_x = -1;
	init_keys(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_error_msg("Initialization failed"));
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (ft_error_msg("Initialization failed"));
	if (!init_mlx_image(game))
		return (ft_error_msg("Initialization failed"));
	if (!load_all_textures(game))
		return (0);
	return (1);
}
