/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:23:06 by ygille            #+#    #+#             */
/*   Updated: 2024/11/19 14:57:38 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int		fd;
// 	int		i;
// 	char	*str;

// 	fd = open("files/1char.txt", O_RDONLY);
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
