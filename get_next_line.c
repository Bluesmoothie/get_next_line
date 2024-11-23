/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:23:06 by ygille            #+#    #+#             */
/*   Updated: 2024/11/23 16:36:04 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*mem;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	res = read_buff(fd, &mem);
	if (mem != NULL)
		mem = update_mem(mem);
	return (res);
}

char	*read_buff(int fd, char **mem)
{
	char		buff[BUFFER_SIZE + 1];
	char		*tmp;
	static int	state = 1;

	if (state == 0 && *mem == NULL)
		return (NULL);
	while (ft_strchr(*mem, '\n') == NULL && state > 0)
	{
		state = read(fd, buff, BUFFER_SIZE);
		if (state > 0)
			buff[state] = '\0';
		if (ft_strchr(*mem, '\n') || state == 0)
			return (extract_line(mem));
		else
		{
			tmp = *mem;
			*mem = ft_strjoin(*mem, buff);
			if (tmp != NULL)
				free(tmp);
		}
	}
	return (extract_line(mem));
}

char	*extract_line(char **mem)
{
	char	*res;
	int		i;

	i = 0;
	if (*mem == NULL)
		return (NULL);
	if (ft_strlen(*mem) == 0)
	{
		free (*mem);
		*mem = NULL;
		return (NULL);
	}
	while (*mem[i] != '\n' && *mem[i] != '\0')
		i++;
	res = ft_calloc(i + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (*mem[i] != '\n' && *mem[i] != '\0')
	{
		res[i] = *mem[i];
		i++;
	}
	return (res);
}

char	*update_mem(char *mem)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if (mem == NULL)
		return (NULL);
	while (mem[i] != '\n' && mem[i] != '\0')
		i++;
	tmp = mem;
	mem = ft_calloc(i + 1, sizeof(char));
	if (mem == NULL)
		return (NULL);
	i = 0;
	while (tmp[i] != '\n' && tmp[i] != '\0')
	{
		mem[i] = tmp[i];
		i++;
	}
	mem[i] = '\0';
	free(tmp);
	return (mem);
}

#include <fcntl.h>
#include <stdio.h>
int	main(int argc, char *argv[])
{
	int		fd;
	int		i;
	char	*str;

	(void) argc;
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
