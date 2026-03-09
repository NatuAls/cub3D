/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <nalesso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:52:46 by nalesso           #+#    #+#             */
/*   Updated: 2026/02/03 17:58:24 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tex(t_tex *tex)
{
	if (tex->path_ea)
		free(tex->path_ea);
	if (tex->path_no)
		free(tex->path_no);
	if (tex->path_so)
		free(tex->path_so);
	if (tex->path_we)
		free(tex->path_we);
}

static void	free_tex_images(t_game *game)
{
	if (game->tex.img_no.img && game->mlx)
		mlx_destroy_image(game->mlx, game->tex.img_no.img);
	if (game->tex.img_so.img && game->mlx)
		mlx_destroy_image(game->mlx, game->tex.img_so.img);
	if (game->tex.img_we.img && game->mlx)
		mlx_destroy_image(game->mlx, game->tex.img_we.img);
	if (game->tex.img_ea.img && game->mlx)
		mlx_destroy_image(game->mlx, game->tex.img_ea.img);
}

void	free_game(t_game *game)
{
	free_tex_images(game);
	if (game->frame.img && game->mlx)
		mlx_destroy_image(game->mlx, game->frame.img);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_map(game);
	if (game->list)
		free_mapl(game->list);
	free_tex(&game->tex);
}
