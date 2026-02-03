#include "cub3d.h"

static int	check_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	find_player(t_game *game)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			c = game->map.grid[y][x];
			if (check_player_char(c))
			{
				init_player(game, c, x + 0.5, y + 0.5);
				game->map.grid[y][x] = '0';
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
