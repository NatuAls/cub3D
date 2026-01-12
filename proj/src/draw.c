#include "cub3d.h"

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

int	get_wall_color(t_ray *ray)
{
	int	color;

	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			color = 0xFF0000;
		else
			color = 0x00FF00;
	}
	else
	{
		if (ray->step_y > 0)
			color = 0x0000FF;
		else
			color = 0xFFFF00;
	}
	if (ray->side == 1)
		color = (color >> 1) & 0x7F7F7F;
	return (color);
}

void	draw_ver_line(t_game *game, int x, t_draw *draw)
{
	int	y;

	y = 0;
	while (y < draw->draw_start)
	{
		put_pixel(&game->frame, x, y, game->ceiling.hex);
		y++;
	}
	while (y < draw->draw_end)
	{
		put_pixel(&game->frame, x, y, draw->color);
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		put_pixel(&game->frame, x, y, game->floor.hex);
		y++;
	}
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	t_draw	draw;

	calc_draw_params(ray, &draw);
	draw.color = get_wall_color(ray);
	draw_ver_line(game, x, &draw);
}