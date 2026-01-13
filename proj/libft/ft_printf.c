/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:47:14 by nalesso           #+#    #+#             */
/*   Updated: 2024/11/30 16:54:26 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	format_check(char const *format, va_list args)
{
	int	count;
	int	ret;

	count = 0;
	if (*format == 'c')
		ret = ft_printchar(va_arg(args, int));
	else if (*format == 's')
		ret = ft_printstr(va_arg(args, char *));
	else if (*format == 'p')
		ret = ft_printptr(va_arg(args, void *));
	else if (*format == 'd' || *format == 'i')
		ret = ft_printint(va_arg(args, int));
	else if (*format == 'u')
		ret = ft_printuint(va_arg(args, unsigned int));
	else if (*format == 'x' || *format == 'X')
		ret = ft_printhex(va_arg(args, unsigned int), *format);
	else if (*format == '%')
		ret = ft_printchar('%');
	else
		ret = ft_printstr("(unknown format)");
	if (ret == -1)
		return (-1);
	count += ret;
	return (count);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		count;
	int		ret;

	va_start(args, str);
	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ret = format_check(str, args);
		}
		else
			ret = ft_printchar(*str);
		if (ret == -1)
			return (va_end(args), -1);
		count += ret;
		str++;
	}
	va_end(args);
	return (count);
}
