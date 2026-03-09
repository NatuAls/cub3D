/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:49:07 by nalesso           #+#    #+#             */
/*   Updated: 2024/10/15 13:56:58 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*p_dest;
	unsigned const char	*p_src;

	if (n == 0 || !dest || !src)
		return (dest);
	p_dest = (unsigned char *)dest;
	p_src = (unsigned const char *)src;
	if (p_dest < p_src)
		return (ft_memcpy(dest, src, n));
	while (n--)
		p_dest[n] = p_src[n];
	return (dest);
}
