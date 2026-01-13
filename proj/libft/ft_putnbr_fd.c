/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:06:30 by nalesso           #+#    #+#             */
/*   Updated: 2024/11/30 15:58:50 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	digit;

	if (n == -2147483648)
	{
		if (write (fd, "-2", 2) == -1)
			return (-1);
		n = 147483648;
	}
	else if (n < 0)
	{
		if (write (fd, "-", 1) == -1)
			return (-1);
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	digit = (n % 10) + '0';
	if (write (fd, &digit, 1) == -1)
		return (-1);
	return (1);
}
