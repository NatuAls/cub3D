#include "cub3d.h"

int get_max_width(t_mapl *list)
{
    t_mapl  *tmp;
    int         res;

    res = 0;
    tmp = list;
    while (tmp)
    {
        if (tmp->len > res)
			res = tmp->len;
        tmp = tmp->next;
    }
    return (res);
}

int	fill_line(t_mapl *list, int max_width)
{
	char	*new_line;

	new_line = malloc(sizeof(char) * (max_width + 1));
	if (!new_line)
		return (ft_error_sys("malloc"));
	ft_memcpy(new_line, list->line, list->len);
	ft_memset(new_line + list->len, ' ', max_width - list->len);
	new_line[max_width] = '\0';
    free(list->line);
    list->line = new_line;
	return (1);
}

int	normalize_map(t_game *game)
{
    t_mapl  *tmp;
    int     i;

	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (ft_error_sys("malloc"));
    i = 0;
	game->map.width = get_max_width(game->list);
    tmp = game->list;
	while (tmp)
	{
        if (tmp->len < game->map.width)
            fill_line(tmp, game->map.width);
		game->map.grid[i] = strdup(tmp->line);
		if (!game->map.grid[i])
			return (ft_error_sys("malloc"));
		i++;
        tmp = tmp->next;
	}
	game->map.grid[i] = NULL;
	return (1);
}

int	check_neighbors(t_map *map, int x, int y)
{
	if (y == 0 || y == map->height - 1)
		return (0);
	if (x == 0 || x == map->width - 1)
		return (0);
	if (map->grid[y-1][x] == ' ')
		return (0);
	if (map->grid[y+1][x] == ' ')
		return (0);
	if (map->grid[y][x-1] == ' ')
		return (0);
	if (map->grid[y][x+1] == ' ')
		return (0);
	return (1);
}

static int	check_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	handle_player_pos(t_game *game, char c, int x, int y)
{
	if (check_player_char(c))
	{
		if (game->player.initialized)
			return (ft_error_msg("There can only be one player"));
		init_player(game, c, x + 0.5, y + 0.5);
		game->map.grid[y][x] = '0';
		if (!check_neighbors(&game->map, x, y))
			return (ft_error_msg("The map should be surrounded by walls"));
	}
	return (1);
}

int validate_map(t_game *game)
{
	int		y;
	int		x;
	char	c;

    if (!normalize_map(game))
		return (0);
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = game->map.grid[y][x];
			if (!handle_player_pos(game, c, x, y))
				return (0);
			if (c == '0' && !check_neighbors(&game->map, x, y))
				return (ft_error_msg("The map should be surrounded by walls"));
			if (c != '1' && c != ' ' && c != '0' && !check_player_char(c))
				return (ft_error_msg("Invalid character on the map"));
			x++;
		}
		y++;
	}
    return (1);
}