/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:47:44 by aogbi             #+#    #+#             */
/*   Updated: 2023/11/21 04:29:30 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	if ((char)c == *s)
		return ((char *)s);
	return (NULL);
}
