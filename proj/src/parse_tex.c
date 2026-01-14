#include "cub3d.h"

void	init_tex(t_game *game)
{
	game->tex.path_no = NULL;
	game->tex.path_so = NULL;
	game->tex.path_we = NULL;
	game->tex.path_ea = NULL;
}

char	*get_tex(char *line)
{
	char	*tmp;
	int		i;

	i = 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	tmp = ft_substr(line, i, ft_strlen(line));
	return (tmp);
}

int	set_tex(t_game *game, char *line)
{
	if (!ft_strncmp(line, "NO", 2) && !game->tex.path_no)
		game->tex.path_no = get_tex(line);
	else if (!ft_strncmp(line, "SO", 2) && !game->tex.path_so)
		game->tex.path_so = get_tex(line);
	else if (!ft_strncmp(line, "WE", 2) && !game->tex.path_we)
		game->tex.path_we = get_tex(line);
	else if (!ft_strncmp(line, "EA", 2) && !game->tex.path_ea)
		game->tex.path_ea = get_tex(line);
	else
		return (0);
	return (1);
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
	if(set_tex(game, tmp))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (-1);
}

int	parse_tex(t_game *game, int fd)
{
	char	*line;
	int		i;
	int		res;

	i = 0;
	while (i < 4)
	{
		line = get_next_line(fd, 0);
		if (!line)
			break ;
		res = analize_line(game, line);
		if (res == -1)
			return (ft_error_msg("Invalid line in textures"));	
		i += res;
	}
	if (i < 4)
		return (ft_error_msg("Missing textures or EOF"));
	return (1);
}
