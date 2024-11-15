/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:23:06 by ygille            #+#    #+#             */
/*   Updated: 2024/11/15 19:28:08 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static int		state;
	char			*line;
	char			buff;

	line = NULL;
	buff = 0;
	state = read(fd, &buff, 1);
	while (state == 1 && buff != '\n')
	{
		line = add_char(buff, line);
		if (line == NULL)
			return (NULL);
		state = read(fd, &buff, 1);
	}
	if (line == NULL && (buff == '\n' || state == 0))
	{
		state = -2;
		return (empty_line());
	}
	if ((state == 0 || state == -1 || state == -2) && line == NULL)
		return (NULL);
	else
		return (line);
}

char	*add_char(char c, char *line)
{
	char	*tmp;

	if (line == NULL)
	{
		line = malloc(sizeof(char) * 2);
		if (line == NULL)
			return (line);
		line[0] = c;
		line[1] = '\0';
		return (line);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (tmp == NULL)
		return (protect(line));
	ft_strlcpy(tmp, line, ft_strlen(line) + 1);
	free(line);
	line = malloc(sizeof(char) * (ft_strlen(tmp) + 2));
	if (line == NULL)
		return (protect(tmp));
	ft_strlcpy(line, tmp, ft_strlen(tmp) + 1);
	line[ft_strlen(tmp)] = c;
	line[ft_strlen(tmp) + 1] = '\0';
	free(tmp);
	return (line);
}

char	*empty_line(void)
{
	char	*line;

	line = malloc(sizeof(char));
	if (line == NULL)
		return (line);
	line[0] = '\0';
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	int	fd;

	fd = open("files/nl", O_RDONLY);
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	return (0);
}
