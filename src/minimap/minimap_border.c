#include "cub3d.h"

static void draw_border_vertical(t_img *img, t_rect *b, int c)
{
    int i;
    int s;

    s = 0;
    while (s <= 3)
    {
        i = -3;
        while (i < b->height)
        {
            put_pixel(img, b->x - s, b->y + i, c);
            put_pixel(img, b->x + b->width + s, b->y + i, c);
            i++;
        }
        s++;
    }
}

static void draw_border_horizontal(t_img *img, t_rect *b, int c)
{
    int i;
    int s;

    s = 0;
    while (s <= 3)
    {
        i = -3;
        while (i <= b->width + 3)
        {
            put_pixel(img, b->x + i, b->y - s, c);
            put_pixel(img, b->x + i, b->y + b->height + s, c);
            i++;
        }
        s++;
    }
}

void    draw_minimap_border(t_game *game, t_rect *b)
{
    draw_border_vertical(&game->frame, b, 0xCCCCCC);
    draw_border_horizontal(&game->frame, b, 0xCCCCCC);
}