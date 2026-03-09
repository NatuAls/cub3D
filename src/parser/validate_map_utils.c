/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <nalesso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:52:30 by nalesso           #+#    #+#             */
/*   Updated: 2026/02/03 17:58:24 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_max_width(t_mapl *list)
{
	t_mapl	*tmp;
	int		res;

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

static int	fill_line(t_mapl *list, int max_width)
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
	t_mapl	*tmp;
	int		i;

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
		game->map.grid[i] = ft_strdup(tmp->line);
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
	if (map->grid[y - 1][x] == ' ')
		return (0);
	if (map->grid[y + 1][x] == ' ')
		return (0);
	if (map->grid[y][x - 1] == ' ')
		return (0);
	if (map->grid[y][x + 1] == ' ')
		return (0);
	return (1);
}
