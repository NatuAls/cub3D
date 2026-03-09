/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:47:45 by nalesso           #+#    #+#             */
/*   Updated: 2024/11/30 14:38:16 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr(char *str)
{
	int	count;

	if (!str)
		str = "(null)";
	count = ft_strlen(str);
	if (ft_putstr_fd(str, 1) == -1)
		return (-1);
	return (count);
}
