#include "cub3d.h"

static int	load_texture(t_game *game, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		return (0);
	return (1);
}

int	load_all_textures(t_game *game)
{
	if (!load_texture(game, &game->tex.img_no, game->tex.path_no))
		return (ft_error_msg("Failed to load north texture"));
	if (!load_texture(game, &game->tex.img_so, game->tex.path_so))
		return (ft_error_msg("Failed to load south texture"));
	if (!load_texture(game, &game->tex.img_we, game->tex.path_we))
		return (ft_error_msg("Failed to load west texture"));
	if (!load_texture(game, &game->tex.img_ea, game->tex.path_ea))
		return (ft_error_msg("Failed to load east texture"));
	return (1);
}

int	get_texture_pixel(t_img *tex, int x, int y)
{
	int	offset;

	offset = y * tex->line_len + x * (tex->bpp / 8);
	return (*(int *)(tex->addr + offset));
}
