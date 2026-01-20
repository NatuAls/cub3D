#include "cub3d.h"

void	init_identifiers(t_game *game)
{
	game->tex.path_no = NULL;
	game->tex.path_so = NULL;
	game->tex.path_we = NULL;
	game->tex.path_ea = NULL;
	game->ceiling.hex = -1;
	game->floor.hex = -1;
}

int	parser(t_game *game, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_error_sys("open"));
	init_identifiers(game);
	if (!parse_identifiers(game, fd))
	{
		get_next_line(fd, 1);
		return (close(fd), 0);
	}
	if (!parse_map(game, fd))
	{
		get_next_line(fd, 1);
		return(close(fd), 0);
	}
	get_next_line(fd, 1);
	return (close(fd), 1);
}
