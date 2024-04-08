/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:40:30 by aogbi             #+#    #+#             */
/*   Updated: 2023/11/21 21:11:57 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	while (*big)
	{
		if (!little[i])
			return ((char *)(big - i));
		else if (*big == little[i])
		{
			i++;
			big++;
		}
		else
		{
			len += i;
			big += (-i + 1);
			i = 0;
		}
		if (!len)
			return (NULL);
		--len;
	}
	if (!*big && !little[i])
		return ((char *)big - i);
	return (NULL);
}
