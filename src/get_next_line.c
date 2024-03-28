/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:55:20 by aogbi             #+#    #+#             */
/*   Updated: 2024/03/28 08:57:40 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

void	ft_strjoin_get(char **s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new;

	if (!*s1 && !s2)
		return ;
	len1 = 0;
	len2 = 0;
	if (*s1)
		len1 = ft_strlen_get(*s1);
	len2 = ft_strlen_get(s2);
	new = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new)
		return ;
	*new = '\0';
	if (*s1)
		ft_strlcat_get(new, *s1, len1 + 1);
	free_memory(s1);
	*s1 = new;
	ft_strlcat_get(*s1, s2, len1 + len2 + 1);
}

static char	*helpreadfromfile(char *buffer, int bytesread, char **stavar,
		char *line)
{
	char	*tmp;

	buffer[bytesread] = '\0';
	tmp = ft_strchr(buffer, '\n');
	if (tmp)
	{
		*stavar = ft_strdup_get(tmp + 1);
		*(tmp) = '\0';
	}
	ft_strjoin_get(&line, buffer);
	return (line);
}

static char	*helpfunction(int fd, char *line, char **stavar)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytesread;

	while (1)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1 || (bytesread == 0 && !line))
		{
			free_memory(&line);
			return (NULL);
		}
		else if (bytesread == 0)
			break ;
		line = helpreadfromfile(buffer, bytesread, stavar, line);
		if (*stavar)
			break ;
	}
	return (line);
}

static char	*readfromfile(int fd, char **stavar, char *line)
{
	char	*tmp;

	if (*stavar)
	{
		if (!**stavar)
			free_memory(stavar);
		line = ft_strdup_get(*stavar);
		free_memory(stavar);
		tmp = ft_strchr(line, '\n');
		if (tmp)
		{
			*stavar = ft_strdup_get(tmp + 1);
			*(tmp) = '\0';
			return (line);
		}
	}
	line = helpfunction(fd, line, stavar);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stavar;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	line = readfromfile(fd, &stavar, line);
	if (!stavar && !line)
	{
		free_memory(&line);
		return (NULL);
	}
	return (line);
}
