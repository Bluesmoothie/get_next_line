/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:23:06 by ygille            #+#    #+#             */
/*   Updated: 2024/11/15 18:10:07 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int		state;
	char	*line;
	char	buff;

	state = 1;
	line = NULL;
	buff = 0;
	while (state == 1 && buff != '\n')
	{
		state = read(fd, &buff, 1);
		if (state == 1 && buff != '\n')
		{
			if (add_char(buff, line) == NULL)
				return (NULL);
		}
	}
	if ((state == 0 || state == -1) && line == NULL)
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
int	main(void)
{
	printf("%s\n", get_next_line(open("test.txt")));
	return (0);
}
