/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <nalesso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:52:37 by nalesso           #+#    #+#             */
/*   Updated: 2026/02/03 17:58:24 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	calc_wall_x(t_game *game, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x = wall_x - floor(wall_x);
	return (wall_x);
}

static t_img	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (&game->tex.img_ea);
		else
			return (&game->tex.img_we);
	}
	else
	{
		if (ray->step_y > 0)
			return (&game->tex.img_so);
		else
			return (&game->tex.img_no);
	}
}

static int	calc_tex_x(t_ray *ray, t_img *tex, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex->width);
	if (ray->side == 0 && ray->dir_x < 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->dir_y > 0)
		tex_x = tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

void	calc_draw_params(t_ray *ray, t_draw *draw)
{
	draw->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	draw->draw_start = -draw->line_height / 2 + WIN_HEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + WIN_HEIGHT / 2;
	if (draw->draw_end >= WIN_HEIGHT)
		draw->draw_end = WIN_HEIGHT - 1;
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	t_draw	draw;
	t_img	*tex;
	double	wall_x;
	int		tex_x;

	calc_draw_params(ray, &draw);
	draw.x = x;
	tex = select_texture(game, ray);
	wall_x = calc_wall_x(game, ray);
	tex_x = calc_tex_x(ray, tex, wall_x);
	draw_ceiling_floor(game, &draw);
	draw_wall_stripe(game, &draw, tex, tex_x);
}
