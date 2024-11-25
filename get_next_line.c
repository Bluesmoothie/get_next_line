/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:23:06 by ygille            #+#    #+#             */
/*   Updated: 2024/11/25 12:23:49 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*mem;
	char		*buff;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	res = read_buff(fd, &mem, buff);
	free(buff);
	if (mem != NULL)
		mem = update_mem(mem);
	return (res);
}

char	*read_buff(int fd, char **mem, char *buff)
{
	char		*tmp;
	static int	state = 1;

	if (state == 0 && *mem == NULL)
		return (NULL);
	while (ft_strchr(*mem, '\n') == NULL && state > 0)
	{
		state = read(fd, buff, BUFFER_SIZE);
		if (state < 0)
			return (free_on_error(mem, &state));
		if (state > 0)
			buff[state] = '\0';
		if (state != 0)
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
	if (check_mem(mem))
		return (NULL);
	while ((*mem)[i] != '\n' && (*mem)[i] != '\0')
		i++;
	if ((*mem)[i] == '\n')
		i++;
	res = malloc((i + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while ((*mem)[i] != '\n' && (*mem)[i] != '\0')
	{
		res[i] = (*mem)[i];
		i++;
	}
	if ((*mem)[i] == '\n')
		res[i++] = '\n';
	res[i] = '\0';
	return (res);
}

char	*update_mem(char *mem)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (mem == NULL)
		return (NULL);
	while (mem[i] != '\n' && mem[i] != '\0')
		i++;
	if (mem[i] == '\n')
		i++;
	tmp = mem;
	mem = malloc((ft_strlen(&mem[i]) + 1) * sizeof(char));
	if (mem == NULL)
		return (NULL);
	while (tmp[i] != '\0')
		mem[j++] = tmp[i++];
	mem[j] = '\0';
	free(tmp);
	return (mem);
}

int	check_mem(char **mem)
{
	if (*mem == NULL)
		return (1);
	if (ft_strlen(*mem) == 0)
	{
		free (*mem);
		*mem = NULL;
		return (1);
	}
	return (0);
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main(int argc, char *argv[])
// {
// 	int		fd;
// 	int		i;
// 	char	*str;

// 	(void) argc;
// 	fd = open(argv[1], O_RDONLY);
// 	str = get_next_line(fd);
// 	i = 1;
// 	while (str)
// 	{
// 		printf("Line %d = |%s|\n", i, str);
// 		free(str);
// 		str = get_next_line(fd);
// 		i++;
// 	}
// 	printf("End");
// 	close(fd);
// 	return (0);
// }
