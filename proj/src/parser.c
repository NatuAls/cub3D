#include "cub3d.h"

int	parser(t_game *game, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_error_sys("open"));
	if (!parse_tex(game, fd))
		return (0);
	return (1);
}
