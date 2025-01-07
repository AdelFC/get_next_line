/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:15:03 by afodil-c          #+#    #+#             */
/*   Updated: 2025/01/07 09:58:04 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_replace(char *buffer)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (0);
	}
	tmp = ft_calloc(sizeof(char), ft_strlen(buffer) - i);
	if (!tmp)
		return (0);
	i++;
	j = 0;
	while (buffer[i])
		tmp[j++] = buffer[i++];
	free(buffer);
	return (tmp);
}

char	*ft_extract(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer || !buffer[i])
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), i + 2);
	if (!line)
		return (0);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*ft_buffer(int fd, char *buffer)
{
	char	*tmp;
	int		bytes;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	if (!buffer)
		return (0);
	while (1)
	{
		tmp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!tmp)
			return (0);
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(tmp);
			return (0);
		}
		buffer = ft_strjoin(buffer, tmp);
		if (!buffer)
			return (0);
		free(tmp);
		if (bytes == 0 || ft_newline(buffer))
			break ;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	buffer = ft_buffer(fd, buffer);
	if (!buffer)
		return (0);
	line = ft_extract(buffer);
	buffer = ft_replace(buffer);
	return (line);
}
