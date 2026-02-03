#include "cub3d.h"

void    draw_minimap(t_game *game)
{
    t_rect tile;
    int     margin;
    int     tile_size;

    margin = 20;
    tile_size = 12;
    tile.width = tile_size;
    tile.height = tile_size;
    draw_minimap_tiles(game, &tile, margin);
    draw_minimap_player(game, margin, tile_size);
    tile.x = margin;
    tile.y = margin;
    tile.width = tile_size * 21;
    tile.height = tile_size * 13;
    draw_minimap_border(game, &tile);
}