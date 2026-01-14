#include "cub3d.h"

int	validate_args(int argc, char **argv)
{
	char	*str;
	int	fd;

	if (argc != 2)
		return (ft_error_msg("There should only be one .cub extension argument."));
	str = ft_strrchr(argv[1], '.');
	if (str && !ft_strncmp(str, ".cub", 5))
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (ft_error_sys("open"));
		close(fd);
		return (1);
	}
	return (ft_error_msg("Invalid file extension: must be .cub"));
}

int	ft_error_msg(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

int	ft_error_sys(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

void	free_map(t_game *game)
{
	int	i;

	if (!game->map.grid)
		return ;
	i = 0;
	while (game->map.grid[i])
	{
		free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
}

void	free_game(t_game *game)
{
	if (game->frame.img && game->mlx)
		mlx_destroy_image(game->mlx, game->frame.img);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_map(game);
}
