#include "cub3d.h"

void	init_colors(t_game *game)
{
	game->floor.r = 100;
	game->floor.g = 100;
	game->floor.b = 100;
	game->floor.hex = (100 << 16) | (100 << 8) | 100;
	game->ceiling.r = 50;
	game->ceiling.g = 50;
	game->ceiling.b = 80;
	game->ceiling.hex = (50 << 16) | (50 << 8) | 80;
}

int	copy_map_lines(t_game *game, char **lines)
{
	int	i;
	int	len;

	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (0);
	i = 0;
	game->map.width = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = strdup(lines[i]);
		if (!game->map.grid[i])
			return (0);
		len = ft_strlen_safe(game->map.grid[i]);
		if (len > game->map.width)
			game->map.width = len;
		i++;
	}
	game->map.grid[i] = NULL;
	return (1);
}

int	init_hardcoded_map(t_game *game)
{
	static char	*lines[] = {
		"11111111",
		"10001001",
	    "10001001",
		"10111001",
		"1000N001",
		"10000001",
		"10000001",
		"11111111",
		NULL
	};
	game->map.height = 8;
	if (!copy_map_lines(game, lines))
		return (0);
	init_colors(game);
	return (1);
}

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