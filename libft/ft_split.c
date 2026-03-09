/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:50:05 by nalesso           #+#    #+#             */
/*   Updated: 2024/10/16 14:14:53 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c && !in_word)
		{
			count++;
			in_word = 1;
		}
		if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

char	*dup_word(char const *s, int start, int end)
{
	char	*str;

	str = malloc ((end - start + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, end - start + 1);
	return (str);
}

void	free_str_array(char **str_array, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(str_array[i]);
		i++;
	}
	free(str_array);
}

int	split_and_fill(char **str_array, char const *s, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			str_array[j] = dup_word(s, start, i);
			if (!str_array[j])
			{
				free_str_array(str_array, j);
				return (0);
			}
			j++;
		}
		else
			i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str_array;

	if (!s)
		return (NULL);
	str_array = malloc ((count_words(s, c) + 1) * sizeof(char *));
	if (!str_array)
		return (NULL);
	if (split_and_fill(str_array, s, c) == 0)
		return (NULL);
	str_array[count_words(s, c)] = NULL;
	return (str_array);
}
