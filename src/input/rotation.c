/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <nalesso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:53:04 by nalesso           #+#    #+#             */
/*   Updated: 2026/02/05 17:21:46 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos_a - p->dir_y * sin_a;
	p->dir_y = old_dir_x * sin_a + p->dir_y * cos_a;
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos_a - p->plane_y * sin_a;
	p->plane_y = old_plane_x * sin_a + p->plane_y * cos_a;
}

void	rotate_left(t_game *game)
{
	rotate_player(&game->player, -ROT_SPEED);
}

void	rotate_right(t_game *game)
{
	rotate_player(&game->player, ROT_SPEED);
}

int	mouse_move(int x, int y, t_game *game)
{
	double	delta;
	double	angle;

	(void)y;
	if (game->last_mouse_x == -1)
		game->last_mouse_x = x;
	delta = x - game->last_mouse_x;
	angle = delta * M_ROT_SPEED;
	rotate_player(&game->player, angle);
	game->last_mouse_x = x;
	return (0);
}
