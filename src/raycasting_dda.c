#include "cub3d.h"

static int	is_out_of_bounds(t_game *game, t_ray *ray)
{
	int	row_len;

	if (ray->map_y < 0 || ray->map_y >= game->map.height)
		return (1);
	row_len = ft_strlen(game->map.grid[ray->map_y]);
	if (ray->map_x < 0 || ray->map_x >= row_len)
		return (1);
	return (0);
}

static int	is_wall_hit(t_game *game, t_ray *ray)
{
	if (is_out_of_bounds(game, ray))
		return (1);
	if (game->map.grid[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

static void	step_ray(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		step_ray(ray);
		if (is_wall_hit(game, ray))
			ray->hit = 1;
	}
}
