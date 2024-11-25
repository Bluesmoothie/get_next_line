/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:23:13 by ygille            #+#    #+#             */
/*   Updated: 2024/11/25 16:39:24 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	100000
# endif

# define MAX_INT		2147483647

# include <unistd.h>
# include <stdlib.h>

//get_next_line.c
char	*get_next_line(int fd);
char	*read_buff(int fd, char **mem, char *buff, int *state);
char	*extract_line(char **mem);
char	*update_mem(char *mem);
int		check_mem(char **mem);

//get_next_line_utils.c
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);

#endif