/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:47:16 by nalesso           #+#    #+#             */
/*   Updated: 2024/11/30 16:25:09 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	get_uilen(unsigned int n)
{
	unsigned int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_putuinbr(unsigned int n)
{
	char	digit;

	if (n >= 10)
	{
		ft_putuinbr(n / 10);
	}
	digit = (n % 10) + '0';
	if (write (1, &digit, 1) == -1)
		return (-1);
	return (1);
}

int	ft_printuint(unsigned int nbr)
{
	unsigned int	len;

	len = get_uilen(nbr);
	if (ft_putuinbr(nbr) == -1)
		return (-1);
	return ((int)len);
}
