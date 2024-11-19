/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:23:06 by ygille            #+#    #+#             */
/*   Updated: 2024/11/19 17:57:02 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int		i;
	int		state;
	char	buff[10000];

	i = 0;
	state = read(fd, &buff[i++], 1);
	if (state != 1)
		return (NULL);
	while (i < 10000 && state == 1 && buff[i - 1] != '\n')
		state = read(fd, &buff[i++], 1);
	printf("State = %i buff = %c i = %i\n", state, buff[i], i);
	if (i == 1 && buff[i] == '\n')
		return (empty_line(2));
	if (state == 0 && i > 0)
		i--;
	if (state == 0 && i == 0)
		return (empty_line(1));
	return (alloc_line(buff, i));
}

char	*empty_line(int s)
{
	char	*line;

	printf("Empty %i\n", s);
	line = malloc(sizeof(char) * s);
	if (line == NULL)
		return (line);
	if (s == 2)
	{
		line[0] = '\n';
		line[1] = '\0';
	}
	else if (s == 1)
		line[0] = '\0';
	return (line);
}

char	*alloc_line(char *buff, int size)
{
	char	*line;

	line = malloc(sizeof(char) * size);
	if (line == NULL)
		return (line);
	line[size] = '\0';
	while (size--)
		line[size] = buff[size];
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
int	main(int argc, char *argv[])
{
	int		fd;
	int		i;
	char	*str;

	fd = open(argv[1], O_RDONLY);
	str = get_next_line(fd);
	i = 1;
	while (str)
	{
		printf("Line %d = |%s|\n", i, str);
		free(str);
		str = get_next_line(fd);
		i++;
	}
	printf("End");
	close(fd);
	return (0);
}
