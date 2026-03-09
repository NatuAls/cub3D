/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:50:20 by nalesso           #+#    #+#             */
/*   Updated: 2024/10/15 13:24:47 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_lenght(int n)
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

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	num;

	num = n;
	len = get_lenght(num);
	str = malloc ((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
	{
		num = -num;
		str[0] = '-';
	}
	else if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		len--;
		str[len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
