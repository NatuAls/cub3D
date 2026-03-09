/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhea <arhea@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:52:15 by nalesso           #+#    #+#             */
/*   Updated: 2026/02/03 22:59:24 by arhea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_tex_path(char **identifier, char *line)
{
	int		i;

	if (*identifier)
		return (ft_error_msg("Duplicate texture identifier"));
	i = 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	*identifier = ft_substr(line, i, ft_strlen(line) - i);
	if (!*identifier)
		return (ft_error_sys("malloc"));
	return (1);
}

int	parse_line_content(t_game *game, char *line)
{
	int	res;

	if (!ft_strncmp(line, "NO", 2))
		res = parse_tex_path(&game->tex.path_no, line);
	else if (!ft_strncmp(line, "SO", 2))
		res = parse_tex_path(&game->tex.path_so, line);
	else if (!ft_strncmp(line, "WE", 2))
		res = parse_tex_path(&game->tex.path_we, line);
	else if (!ft_strncmp(line, "EA", 2))
		res = parse_tex_path(&game->tex.path_ea, line);
	else if (line[0] == 'C')
		res = parse_color(&game->ceiling, line);
	else if (line[0] == 'F')
		res = parse_color(&game->floor, line);
	else
		return (ft_error_msg("Invalid identifier"));
	return (res);
}

int	analyze_line(t_game *game, char *line)
{
	char	*tmp;

	tmp = ft_strtrim(line, " \n\t");
	free(line);
	if (!tmp)
		return (-1);
	if (tmp[0] == '\0')
	{
		free(tmp);
		return (0);
	}
	if (parse_line_content(game, tmp))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (-1);
}

int	parse_identifiers(t_game *game, int fd)
{
	char	*line;
	int		i;
	int		res;

	i = 0;
	while (i < 6)
	{
		line = get_next_line(fd, 0);
		if (!line)
			break ;
		res = analyze_line(game, line);
		if (res == -1)
			return (0);
		i += res;
	}
	if (i < 6)
		return (ft_error_msg("Missing identifiers or EOF"));
	return (1);
}
