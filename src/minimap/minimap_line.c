/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:46:02 by nalesso           #+#    #+#             */
/*   Updated: 2026/02/03 17:46:04 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void line_step(t_img *img, t_line *l)
{
    int i;

    i = 0;
    while (i < l->steps)
    {
        put_pixel(img, (int)l->x, (int)l->y, 0xFF0000);
        l->x += l->dx;
        l->y += l->dy;
        i++;
    }
}


void draw_minimap_line(t_game *game, double bx, double by)
{
    t_line l;
    double ex;
    double ey;

    ex = bx + game->player.dir_x * 10;
    ey = by + game->player.dir_y * 10;
    l.x = bx;
    l.y = by;
    l.dx = ex - bx;
    l.dy = ey - by;
    l.steps = fabs(l.dx) > fabs(l.dy) ? fabs(l.dx) : fabs(l.dy);
    l.dx /= l.steps;
    l.dy /= l.steps;
    line_step(&game->frame, &l);
}
