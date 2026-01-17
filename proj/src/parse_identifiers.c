#include "cub3d.h"

int	set_tex(char **identifier, char *line)
{
	int		i;

	i = 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	*identifier = ft_substr(line, i, ft_strlen(line));
	if (!*identifier)
		return (ft_error_sys("malloc"));
	return (1);
}

int	set_identifiers(t_game *game, char *line)
{
	int	res;

	if (!ft_strncmp(line, "NO", 2) && !game->tex.path_no)
		res = set_tex(&game->tex.path_no, line);
	else if (!ft_strncmp(line, "SO",2) && !game->tex.path_so)
		res = set_tex(&game->tex.path_so, line);
	else if (!ft_strncmp(line, "WE", 2) && !game->tex.path_we)
		res = set_tex(&game->tex.path_we, line);
	else if (!ft_strncmp(line, "EA", 2) && !game->tex.path_ea)
		res = set_tex(&game->tex.path_ea, line);
	else if (line[0] == 'C' && !game->ceiling)
		res = parse_color(&game->ceiling, line);
	else if (line[0] == 'F' && !game->floor)
		res = parse_color(&game->floor, line);
	else
		return (ft_error_msg("The initials of the identifiers are invalid or there are duplicate identifiers."));
	return (res);
}

int	analize_line(t_game *game, char *line)
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
	if(set_identifiers(game, tmp))
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
		res = analize_line(game, line);
		if (res == -1)
			return (0);	
		i += res;
	}
	if (i < 6)
		return (ft_error_msg("Missing identifiers or EOF"));
	return (1);
}
