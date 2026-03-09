/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:02:50 by nalesso           #+#    #+#             */
/*   Updated: 2024/10/07 15:21:57 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	len;	

	len = ft_strlen(s) + 1;
	str = malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, len);
	return (str);
}
