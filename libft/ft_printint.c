/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:24:58 by nalesso           #+#    #+#             */
/*   Updated: 2024/11/30 16:23:36 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_len(int n)
{
	int		len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_printint(int nbr)
{
	int	len;

	len = get_len(nbr);
	if (ft_putnbr_fd(nbr, 1) == -1)
		return (-1);
	return (len);
}
