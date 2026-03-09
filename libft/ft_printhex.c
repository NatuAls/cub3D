/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:17:07 by nalesso           #+#    #+#             */
/*   Updated: 2024/11/30 16:31:39 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	uilength(unsigned int nbr)
{
	unsigned int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		len++;
		nbr /= 16;
	}
	return ((int)len);
}

int	hex_converter(unsigned int nbr, char diff)
{
	if (nbr >= 16)
	{
		hex_converter(nbr / 16, diff);
		hex_converter(nbr % 16, diff);
	}
	else if (nbr <= 9)
	{
		if (ft_putchar_fd(nbr + '0', 1) == -1)
			return (-1);
	}
	else if (diff == 'x')
	{
		if (ft_putchar_fd(nbr - 10 + 'a', 1) == -1)
			return (-1);
	}
	else if (diff == 'X')
	{
		if (ft_putchar_fd(nbr - 10 + 'A', 1) == -1)
			return (-1);
	}
	return (1);
}

int	ft_printhex(unsigned int nbr, char diff)
{
	int	len;

	len = uilength(nbr);
	if (hex_converter(nbr, diff) == -1)
		return (-1);
	return (len);
}
