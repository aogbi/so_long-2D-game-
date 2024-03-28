/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:55:23 by aogbi             #+#    #+#             */
/*   Updated: 2024/03/28 08:57:40 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
size_t	ft_strlen_get(const char *s);
size_t	ft_strlcat_get(char *dst, const char *src, size_t size);
char	*ft_strdup_get(char *s);
char	*ft_strchr(const char *s, int c);
void	free_memory(char **ptr);
void	ft_strjoin_get(char **s1, char *s2);

#endif
