/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:37:14 by nalesso           #+#    #+#             */
/*   Updated: 2024/11/30 16:33:22 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	length_pointer(uintptr_t ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
		return (1);
	while (ptr > 0)
	{
		len++;
		ptr /= 16;
	}
	return (len);
}

int	pointer_converter(uintptr_t decimalptr)
{
	if (decimalptr >= 16)
	{
		pointer_converter(decimalptr / 16);
		pointer_converter(decimalptr % 16);
	}
	else if (decimalptr <= 9)
	{
		if (ft_putchar_fd(decimalptr + '0', 1) == -1)
			return (-1);
	}
	else
	{
		if (ft_putchar_fd(decimalptr - 10 + 'a', 1) == -1)
			return (-1);
	}
	return (1);
}

int	ft_printptr(void *ptr)
{
	uintptr_t	decimalptr;
	int			len;

	if (!ptr)
	{
		if (ft_putstr_fd("(nil)", 1) == -1)
			return (-1);
		return (5);
	}
	decimalptr = (uintptr_t)ptr;
	len = length_pointer(decimalptr) + 2;
	if (ft_printstr("0x") == -1)
		return (-1);
	if (len == 3 && decimalptr == 0)
	{
		if (ft_printchar('0') == -1)
			return (-1);
	}
	else
	{
		if (pointer_converter(decimalptr) == -1)
			return (-1);
	}
	return (len);
}
