/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:42:12 by gangel-a          #+#    #+#             */
/*   Updated: 2025/03/15 21:35:22 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	gnl_ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if ((unsigned char)c == '\0')
		return (i);
	return (-1);
}

static size_t	gnl_ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (gnl_ft_strlen(src));
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (gnl_ft_strlen(src));
}

char	*gnl_ft_strjoin(char *s1, char const *s2)
{
	char	*ptr;
	int		s1_len;
	int		s2_len;

	s1_len = gnl_ft_strlen(s1);
	s2_len = gnl_ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	ptr = malloc(s1_len + s2_len + 1);
	if (!ptr)
		return (NULL);
	gnl_ft_strlcpy(ptr, s1, s1_len + 1);
	gnl_ft_strlcpy((ptr + s1_len), s2, s2_len + 1);
	free(s1);
	return (ptr);
}

char	*gnl_ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	s_len;

	if (!s || !*s)
		return (NULL);
	s_len = gnl_ft_strlen(s);
	if (start >= s_len)
	{
		subs = (char *)malloc(sizeof(char) * 1);
		if (!subs)
			return (NULL);
		subs[0] = '\0';
		return (subs);
	}
	if (s_len - start < len)
		len = s_len - start;
	subs = (char *)malloc(sizeof(char) * (len + 1));
	if (!subs)
		return (NULL);
	gnl_ft_strlcpy(subs, s + start, len + 1);
	return (subs);
}
