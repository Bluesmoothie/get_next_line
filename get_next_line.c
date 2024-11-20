/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:23:06 by ygille            #+#    #+#             */
/*   Updated: 2024/11/20 19:11:37 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1] = "\0";
	char		*res;
	int			i;
	char		tmp[BUFFER_SIZE + 1];

	tmp[0] = '\0';
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	res = read_buff(buff, fd);
	i = 0;
	while (buff[i] != '\0' && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	ft_strlcat(tmp, &buff[i], ft_strlen(&buff[i]) + 1);
	i = 0;
	while (tmp[i] != '\0')
	{
		buff[i] = tmp[i];
		i++;
	}
	buff[i] = '\0';
	return (res);
}

char	*read_buff(char *buff, int fd)
{
	int		state;
	char	*line;

	line = NULL;
	state = 1;
	while (ft_strchr(buff, '\n') == NULL && state > 0)
	{
		state = read(fd, buff, BUFFER_SIZE);
		buff[state] = '\0';
		if (ft_strchr(buff, '\n'))
			return (extract_line(line, buff));
		else
			line = ft_strjoin(line, buff);
	}
	return (extract_line(line, buff));
}

char	*extract_line(char *line, char *buff)
{
	char	*res;
	int		i;

	i = 0;
	while (buff[i] != '\0' && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	res = malloc(sizeof(char) * ft_strlen(line) + i + 1);
	printf("size = %i\n", ft_strlen(line) + i + 1);
	if (res == NULL)
		return (NULL);
	ft_strlcat(res, line, ft_strlen(line) + 1);
	ft_strlcat(res, buff, ft_strlen(line) + i + 1);
	if (line != NULL)
		free(line);
	return (res);
}

#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	int		fd;
	int		i;
	char	*str;

	fd = open("files/lines_around_10.txt", O_RDONLY);
	str = get_next_line(fd);
	i = 1;
	while (i < 10)
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
