/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalesso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:17:03 by nalesso           #+#    #+#             */
/*   Updated: 2025/03/24 20:01:44 by nalesso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*append_buffer(char *basin_buffer, char *cup_buffer)
{
	char	*temp;

	temp = ft_strjoin(basin_buffer, cup_buffer);
	free(basin_buffer);
	return (temp);
}

char	*read_from_file(char *basin_buffer, int fd)
{
	char	*cup_buffer;
	int		bytes_read;

	cup_buffer = ft_calloc(4 + 1, sizeof(char));
	if (!cup_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, cup_buffer, 4);
		if (bytes_read == -1)
			return (free(basin_buffer), free(cup_buffer), NULL);
		if (bytes_read == 0)
			break ;
		cup_buffer[bytes_read] = '\0';
		basin_buffer = append_buffer(basin_buffer, cup_buffer);
		if (ft_strchr(cup_buffer, '\n'))
			break ;
	}
	free(cup_buffer);
	return (basin_buffer);
}

char	*extract_line(char *basin_buffer)
{
	char	*line;
	char	*remaining;
	int		basin_len;

	if (!basin_buffer[0])
		return (NULL);
	remaining = ft_strchr(basin_buffer, '\n');
	if (!remaining)
	{
		basin_len = ft_strlen(basin_buffer);
		line = ft_calloc(basin_len + 1, sizeof(char));
		if (!line)
			return (NULL);
		ft_strlcpy(line, basin_buffer, basin_len + 1);
		return (line);
	}
	line = ft_calloc(remaining - basin_buffer + 2, sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, basin_buffer, remaining - basin_buffer + 2);
	return (line);
}

char	*obtain_remaining(char *basin_buffer)
{
	char	*remaining;
	char	*result;
	int		remaining_len;

	if (!basin_buffer[0])
		return (free(basin_buffer), NULL);
	remaining = ft_strchr(basin_buffer, '\n');
	if (!remaining)
		return (free(basin_buffer), NULL);
	remaining++;
	remaining_len = ft_strlen(remaining);
	result = ft_calloc(remaining_len + 1, sizeof(char));
	if (!result)
		return (free(basin_buffer), NULL);
	ft_strlcpy(result, remaining, remaining_len + 1);
	free(basin_buffer);
	return (result);
}

char	*get_next_line(int fd, int free_buffer)
{
	static char	*basin_buffer;
	char		*line;

	if (free_buffer)
	{
		free(basin_buffer);
		basin_buffer = NULL;
		return (NULL);
	}
	if (fd < 0)
		return (NULL);
	if (!basin_buffer)
		basin_buffer = ft_calloc(1, sizeof(char));
	if (!basin_buffer)
		return (NULL);
	if (!ft_strchr(basin_buffer, '\n'))
		basin_buffer = read_from_file(basin_buffer, fd);
	if (!basin_buffer)
		return (free(basin_buffer), NULL);
	line = extract_line(basin_buffer);
	basin_buffer = obtain_remaining(basin_buffer);
	return (line);
}
