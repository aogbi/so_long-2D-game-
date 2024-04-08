/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:39:30 by aogbi             #+#    #+#             */
/*   Updated: 2023/11/17 17:11:15 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_lenofnum(int n)
{
	unsigned int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	firtchar(long i)
{
	char	c;

	if (!i)
		c = '0';
	else
		c = '-';
	return (c);
}

char	*ft_itoa(int n)
{
	char			*str;
	long			i;
	unsigned int	slen;

	i = (long)n;
	slen = ft_lenofnum(i);
	str = (char *)malloc(sizeof(char) * (slen + 1));
	if (!str)
		return (NULL);
	if (i <= 0)
		str[0] = firtchar(i);
	if (i < 0)
		i *= -1;
	str[slen] = 0;
	while (i)
	{
		str[--slen] = '0' + (i % 10);
		i /= 10;
	}
	return (str);
}
