/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:15:31 by afodil-c          #+#    #+#             */
/*   Updated: 2024/12/10 11:19:01 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	i;

	dst = (char *)malloc(ft_strlen(s1) + 1);
	if (!dst)
		return (0);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*pdest;
	unsigned char	*psrc;

	if (!dest && !src)
		return (0);
	pdest = (unsigned char *)(dest);
	psrc = (unsigned char *)(src);
	while (n)
	{
		*pdest++ = *psrc++;
		n--;
	}
	return (dest);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*psrc;
	char	*pdst;

	if (!dst && !src)
		return (0);
	psrc = (char *)src;
	pdst = (char *)dst;
	if (pdst > psrc)
		while (len-- > 0)
			pdst[len] = psrc[len];
	else
	{
		ft_memcpy(pdst, psrc, len);
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	un_c;

	un_c = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == un_c)
			return ((char *)(s + i));
		i++;
	}
	if (!un_c)
		return ((char *)(s + i));
	return (0);
}
