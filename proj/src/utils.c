#include "cub3d.h"

int	ft_strlen_safe(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	free_map(t_game *game)
{
	int	i;

	if (!game->map.grid)
		return ;
	i = 0;
	while (game->map.grid[i])
	{
		free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
}

void	free_game(t_game *game)
{
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
}