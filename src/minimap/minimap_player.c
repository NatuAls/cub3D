#include "cub3d.h"

void	draw_rect(t_img *img, t_rect *square, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < square->height)
	{
		j = 0;
		while (j < square->width)
		{
			put_pixel(img, square->x + j, square->y + i, color);
			j++;
		}
		i++;
	}
}

void    draw_minimap_player(t_game *game, int margin, int tile_size)
{
    t_rect p;
    int     cx;
    int     cy;

    cx = margin + (10 * tile_size);
    cy = margin + (6 * tile_size);
    p.x = cx + 3;
    p.y = cy + 3;
    p.width = 6;
    p.height = 6;
    draw_rect(&game->frame, &p, 0xFF0000);
    draw_minimap_line(game, p.x + 3, p.y + 3);
}