/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:35:44 by aogbi             #+#    #+#             */
/*   Updated: 2023/11/26 13:03:26 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	nbrtostr(long nb, int fd)
{
	if (nb)
	{
		nbrtostr(nb / 10, fd);
		ft_putchar_fd(nb % 10 + '0', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	if (fd < 0)
		return ;
	nb = (long)n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
	}
	if (nb == 0)
		ft_putchar_fd('0', fd);
	else
		nbrtostr(nb, fd);
}
