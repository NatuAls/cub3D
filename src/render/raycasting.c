/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <nalesso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:52:40 by nalesso           #+#    #+#             */
/*   Updated: 2026/02/03 17:58:24 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

void	calc_step_dist(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y)
			* ray->delta_dist_y;
	}
}

void	calc_wall_dist(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos_x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos_y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	if (ray->perp_wall_dist < 0.0001)
		ray->perp_wall_dist = 0.0001;
}

void	raycast(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game, &ray, x);
		calc_step_dist(game, &ray);
		perform_dda(game, &ray);
		calc_wall_dist(game, &ray);
		draw_column(game, &ray, x);
		x++;
	}
}
