/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:43:55 by nalesso           #+#    #+#             */
/*   Updated: 2024/10/19 14:55:11 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*create_node(t_list *node, void *(*f)(void *), void (*del)(void *))
{
	void	*fcontent;
	t_list	*new_node;

	fcontent = f(node->content);
	if (!fcontent)
		return (NULL);
	new_node = ft_lstnew(fcontent);
	if (!new_node)
	{
		del(fcontent);
		return (NULL);
	}
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstnew;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	lstnew = NULL;
	while (lst)
	{
		new_node = create_node(lst, f, del);
		if (!new_node)
		{
			ft_lstclear(&lstnew, del);
			return (NULL);
		}
		ft_lstadd_back(&lstnew, new_node);
		lst = lst->next;
	}
	return (lstnew);
}
