/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:23:48 by ygille            #+#    #+#             */
/*   Updated: 2024/11/25 12:54:47 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	count;

	count = 0;
	if (s == NULL)
		return (NULL);
	while (c > 127)
		c -= 128;
	while (s[count] != '\0' && s[count] != c)
		count++;
	if (s[count] == c)
		return ((char *)&s[count]);
	else
		return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*join;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = malloc(sizeof(char) * size);
	if (join == NULL)
		return (NULL);
	join[0] = '\0';
	ft_strlcat(join, s1, ft_strlen(s1) + 1);
	ft_strlcat(join, s2, size);
	return (join);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (src == NULL && size == 1)
	{
		dst[0] = '\0';
		return (1);
	}
	if (size == 0)
		return (ft_strlen(src));
	while (dst[i] && i < size)
		i++;
	if (i == size)
		return (i + ft_strlen(src));
	while (src[j] && i + j < size - 1 && src != NULL)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + ft_strlen(src));
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}
