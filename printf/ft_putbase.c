/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:15:39 by aogbi             #+#    #+#             */
/*   Updated: 2023/12/05 15:24:47 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putbase(size_t nbr, char *base, int len)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	len = ft_putstr("0x", len);
	if (nbr < base_len)
	{
		len = ft_putchar(base[nbr % base_len], len);
	}
	else
	{
		len = ft_putnbr_base(nbr / base_len, base, len);
		len = ft_putnbr_base(nbr % base_len, base, len);
	}
	return (len);
}
