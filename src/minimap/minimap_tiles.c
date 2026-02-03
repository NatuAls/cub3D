/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_tiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:50:35 by nalesso           #+#    #+#             */
/*   Updated: 2026/02/03 17:50:37 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_tile(t_game *game, t_rect *tile, int mx, int my)
{
    int color;

    if (mx >= 0 && mx < game->map.width && my >= 0 && my < game->map.height)
    {
        if (game->map.grid[my][mx] == '1')
            color = 0x444444;
        else if (game->map.grid[my][mx] == '0')
            color = 0xC0C0C0;
        else
            color = 0x000000;
    }
    else
        color = 0x000000;
    draw_rect(&game->frame, tile, color);
}


void    draw_minimap_tiles(t_game *game, t_rect *tile, int margin)
{
    int x;
    int y;
    int map_x;
    int map_y;

    y = -6;
    while (y <= 6)
    {
        x = -10;
        while (x <= 10)
        {
            map_x = (int)(game->player.pos_x) + x;
            map_y = (int)(game->player.pos_y) + y;
            tile->x = margin + (x + 10) * tile->width;
            tile->y = margin + (y + 6) * tile->height;
            draw_tile(game, tile, map_x, map_y);
            x++;
        }
        y++;
    }
}
