#include "cub3d.h"

int is_empty_line(char *line)
{
    int i;

    i = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
        i++;
    if (line[i])
        return (0);
    return (1);
}

int    check_empty_end(char *line, int fd)
{
    while (line && is_empty_line(line))
    {
        free(line);
        line = get_next_line(fd, 0);
    }
    if (line)
    {
        free(line);
        return (ft_error_msg("Trash after map or split map detected"));
    }
    return (1);
}

t_mapl *lst_new_map(char *str)
{
    t_mapl *node;

    node = ft_calloc(sizeof(t_mapl), 1);
    if (!node)
    {
        ft_error_sys("ft_calloc");
        return (NULL);
    }
    node->line = str;
    node->next = NULL;
    node->len = ft_strlen(str);
    return (node);
}

int    lst_addback_map(t_mapl *list, char *str)
{
    t_mapl *tmp;

    if (!list || !str)
        return (0);
    tmp = list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = lst_new_map(str);
    if (tmp->next)
        return (1);
    return (0);
}

int read_map_lines(t_game *game, char *line, int fd)
{
    t_mapl *list;
    char    *tmp;
    int     i;

    i = 0;
    while (line && !is_empty_line(line))
    {
        tmp = ft_strtrim(line, "\n");
        if (!tmp)
            return (ft_error_sys("ft_strtrim"));
        if (i == 0)
            list = lst_new_map(tmp);
        else
            lst_addback_map(list, tmp);           
        free(line);
        line = get_next_line(fd, 0);
        i++;
    }
    game->list = list;
    game->map.height = i;
    if (!check_empty_end(line, fd))
        return (0);
    return (1);
}

int parse_map(t_game *game, int fd)
{
    char	*line;

    line = get_next_line(fd, 0);
	while (line && is_empty_line(line))
    {
        free(line);
        line = get_next_line(fd, 0);
    }
    if (!read_map_lines(game, line, fd))
        return (0);
    game->player.initialized = 0;
    if (!validate_map(game))
        return (0);
    if (!game->player.initialized)
		return(ft_error_msg("There should be a player on the map"));
    return (1);
}