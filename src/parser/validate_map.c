/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <nalesso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:52:32 by nalesso           #+#    #+#             */
/*   Updated: 2026/02/03 17:58:24 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	handle_player_pos(t_game *game, char c, int x, int y)
{
	if (check_player_char(c))
	{
		if (game->player.initialized)
			return (ft_error_msg("There can only be one player"));
		init_player(game, c, x + 0.5, y + 0.5);
		game->map.grid[y][x] = '0';
		if (!check_neighbors(&game->map, x, y))
			return (ft_error_msg("The map should be surrounded by walls"));
	}
	return (1);
}

static int	validate_cell(t_game *game, int x, int y)
{
	char	c;

	c = game->map.grid[y][x];
	if (!handle_player_pos(game, c, x, y))
		return (0);
	if (c == '0' && !check_neighbors(&game->map, x, y))
		return (ft_error_msg("The map should be surrounded by walls"));
	if (c != '1' && c != ' ' && c != '0' && !check_player_char(c))
		return (ft_error_msg("Invalid character on the map"));
	return (1);
}

int	validate_map(t_game *game)
{
	int	y;
	int	x;

	if (!normalize_map(game))
		return (0);
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (!validate_cell(game, x, y))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
