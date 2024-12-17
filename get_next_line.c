/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:15:03 by afodil-c          #+#    #+#             */
/*   Updated: 2024/12/17 08:51:03 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *buffer, char *buf)
{
	char	*tmp;
	size_t	buffer_len;
	size_t	buf_len;

	if (!buffer)
		return (ft_strdup(buf));
	buffer_len = ft_strlen(buffer);
	buf_len = ft_strlen(buf);
	tmp = malloc(buffer_len + buf_len + 1);
	if (!tmp)
	{
		free(buffer);
		buffer = 0;
		return (0);
	}
	ft_memcpy(tmp, buffer, buffer_len);
	ft_memcpy(tmp + buffer_len, buf, buf_len + 1);
	free(buffer);
	return (tmp);
}

char	*ft_new_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(i + 1 + (buffer[i] == '\n'));
	if (!line)
		return (0);
	ft_memcpy(line, buffer, i + (buffer[i] == '\n'));
	line[i + (buffer[i] == '\n')] = '\0';
	return (line);
}

char	*ft_next_one(char *buffer)
{
	int		i;
	int		len;
	char	*new_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (0);
	}
	len = ft_strlen(buffer + i + 1);
	new_buffer = malloc(len + 1);
	if (!new_buffer)
	{
		free(buffer);
		return (0);
	}
	ft_memcpy(new_buffer, buffer + i + 1, len);
	new_buffer[len] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*read_file(int fd, char *res)
{
	char	buffer[BUFFER_SIZE + 1];
	int		byte_read;

	if (!res)
		res = ft_strdup("");
	while (!ft_strchr(res, '\n'))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(res);
			return (0);
		}
		if (byte_read == 0)
			return (res);
		buffer[byte_read] = '\0';
		res = ft_free(res, buffer);
		if (!res)
			return (0);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (0);
	if(!*buffer)
	{
		free(buffer);
		buffer = 0;
		return (0);
	}
	line = ft_new_line(buffer);
	buffer = ft_next_one(buffer);
	return (line);
}
