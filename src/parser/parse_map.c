/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <nalesso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:52:27 by nalesso           #+#    #+#             */
/*   Updated: 2026/02/03 17:58:24 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_empty_end(char *line, int fd)
{
	while (line && is_empty_line(line))
	{
		free(line);
		line = get_next_line(fd, 0);
	}
	if (line)
	{
		free(line);
		return (ft_error_msg("Trash after map or split map detected"));
	}
	return (1);
}

static int	read_map_lines(t_game *game, char *line, int fd)
{
	t_mapl	*list;
	char	*tmp;
	int		i;

	i = 0;
	list = NULL;
	while (line && !is_empty_line(line))
	{
		tmp = ft_strtrim(line, "\n");
		if (!tmp)
			return (ft_error_sys("ft_strtrim"));
		if (i == 0)
			list = lst_new_map(tmp);
		else
			lst_addback_map(list, tmp);
		free(line);
		line = get_next_line(fd, 0);
		i++;
	}
	game->list = list;
	game->map.height = i;
	if (!check_empty_end(line, fd))
		return (0);
	return (1);
}

int	parse_map(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd, 0);
	while (line && is_empty_line(line))
	{
		free(line);
		line = get_next_line(fd, 0);
	}
	if (!read_map_lines(game, line, fd))
		return (0);
	game->player.initialized = 0;
	if (!validate_map(game))
		return (0);
	if (!game->player.initialized)
		return (ft_error_msg("There should be a player on the map"));
	return (1);
}
