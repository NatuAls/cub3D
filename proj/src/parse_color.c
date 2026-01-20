#include "cub3d.h"

int is_valid_digit(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return(0);
        i++;
    }
    return (1);
}

int get_color(char *str)
{
    int nbr;

    if (!is_valid_digit(str))
        return (-1);
    nbr = ft_atoi(str);
    if (nbr >= 0 && nbr <= 255)
        return (nbr);
    return (-1);
}

int fill_rgb(t_color *color, char **rgb)
{
    int     i;
    int     nbr;

    i = 0;
    while (rgb[i])
        i++;
    if (i != 3)
        return (ft_error_msg("Invalid color format: must be R,G,B"));
    i = 0;
    while (i < 3)
    {
        nbr = get_color(rgb[i]);
        if (nbr == -1)
            return (ft_error_msg("Invalid color value (0-255) or non-digit"));
        if (i == 0)
            color->r = nbr;
        else if (i == 1)
            color->g = nbr;
        else
            color->b = nbr;
        i++;
    }
    color->hex = color->r << 16 | color->g << 8 | color->b;
    return (1);
}

void    ft_free_matrix(char **str)
{
    int i;

    i = 0;
    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

int	parse_color(t_color *color, char *line)
{
	int		    i;
    char    **rgb;

	i = 1;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
    rgb = ft_split(line + i, ',');
    if (!rgb)
        return (ft_error_sys("split"));
    if (!fill_rgb(color, rgb))
    {
        ft_free_matrix(rgb);
        return (0);
    }
    ft_free_matrix(rgb);
	return (1);
}
