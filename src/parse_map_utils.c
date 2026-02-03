#include "cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i])
		return (0);
	return (1);
}

t_mapl	*lst_new_map(char *str)
{
	t_mapl	*node;

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

int	lst_addback_map(t_mapl *list, char *str)
{
	t_mapl	*tmp;

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
