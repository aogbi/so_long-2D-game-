/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:23:33 by aogbi             #+#    #+#             */
/*   Updated: 2023/11/24 08:47:24 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	numofstr(char const *s, char c)
{
	int	n;
	int	x;
	int	i;

	n = 0;
	i = 0;
	x = 1;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			x = 1;
		}
		else if (s[i++] != c && x)
		{
			x = 0;
			n++;
		}
	}
	return (n);
}

static int	count_char(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] != c)
	{
		while (str[i] != c && str[i])
		{
			i++;
		}
		return (i);
	}
	else
		return (0);
}

static void	free_it(char **ptr, int j)
{
	while (j-- > 0)
	{
		free(ptr[j]);
	}
	free(ptr);
}

static char	**help_split(char const *s, char c, char **ptr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		i = count_char((char *)s, c);
		if (i != 0)
		{
			ptr[j] = ft_substr(s, 0, i);
			if (!ptr[j])
			{
				free_it(ptr, j);
				return (NULL);
			}
			j++;
		}
		s += i;
	}
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char			**str;
	unsigned int	num;

	if (!s)
		return (NULL);
	num = numofstr(s, c);
	str = (char **)malloc(sizeof(char *) * (num + 1));
	if (!str)
		return (NULL);
	str[num] = 0;
	str = help_split((char *)s, c, str);
	return (str);
}
