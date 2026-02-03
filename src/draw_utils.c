#include "cub3d.h"

void	draw_ceiling_floor(t_game *game, t_draw *draw)
{
	int	y;

	y = 0;
	while (y < draw->draw_start)
	{
		put_pixel(&game->frame, draw->x, y, game->ceiling.hex);
		y++;
	}
	y = draw->draw_end;
	while (y < WIN_HEIGHT)
	{
		put_pixel(&game->frame, draw->x, y, game->floor.hex);
		y++;
	}
}

void	draw_wall_stripe(t_game *game, t_draw *draw, t_img *tex, int tex_x)
{
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;

	step = (double)tex->height / (double)draw->line_height;
	tex_pos = (draw->draw_start - WIN_HEIGHT / 2 + draw->line_height / 2);
	tex_pos = tex_pos * step;
	y = draw->draw_start;
	while (y < draw->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = get_texture_pixel(tex, tex_x, tex_y);
		put_pixel(&game->frame, draw->x, y, color);
		tex_pos = tex_pos + step;
		y++;
	}
}
