/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <nalesso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:52:42 by nalesso           #+#    #+#             */
/*   Updated: 2026/02/03 17:58:24 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_frame(t_game *game)
{
	raycast(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}
