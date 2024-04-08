/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:44:50 by aogbi             #+#    #+#             */
/*   Updated: 2023/12/05 15:27:50 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	valid(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(base) < 2)
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	i = 0;
	while (base[i])
	{
		j = i + 1;
		while ((base[i] != base[j]) && base[j])
			j++;
		if (base[i] == base[j])
			return (0);
		i++;
	}
	return (1);
}

int	ft_putnbr_base(long nbr, char *base, int len)
{
	long	base_len;
	long	n;

	if (!valid(base))
		return (len);
	n = nbr;
	if (nbr < 0)
	{
		len = ft_putchar('-', len);
		n *= -1;
	}
	base_len = ft_strlen(base);
	if (n < base_len)
	{
		len = ft_putchar(base[n % base_len], len);
	}
	else
	{
		len = ft_putnbr_base(n / base_len, base, len);
		len = ft_putnbr_base(n % base_len, base, len);
	}
	return (len);
}
