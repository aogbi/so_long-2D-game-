/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:49:34 by aogbi             #+#    #+#             */
/*   Updated: 2023/11/26 13:03:26 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	isset(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	unsigned int	index;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && isset(*s1, set))
		++s1;
	index = ft_strlen((char *)s1);
	while (index && isset(s1[index - 1], set))
		--index;
	str = malloc((index + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, index + 1);
	str[index] = 0;
	return (str);
}
