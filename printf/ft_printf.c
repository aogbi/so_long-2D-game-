/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:08:32 by aogbi             #+#    #+#             */
/*   Updated: 2023/12/05 15:26:47 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	choices(char c, va_list args)
{
	int	len;

	len = 0;
	if (c == 'c')
		len = ft_putchar(va_arg(args, int), len);
	else if (c == 's')
		len = ft_putstr(va_arg(args, char *), len);
	else if (c == 'p')
		len = ft_putbase(va_arg(args, unsigned long), "0123456789abcdef", len);
	else if (c == 'd')
		len = ft_putnbr_base(va_arg(args, int), "0123456789", len);
	else if (c == 'i')
		len = ft_putnbr_base(va_arg(args, int), "0123456789", len);
	else if (c == 'u')
		len = ft_putnbr_base(va_arg(args, unsigned int), "0123456789", len);
	else if (c == 'x')
		len = ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef",
				len);
	else if (c == 'X')
		len = ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF",
				len);
	else if (c == '%')
		len = ft_putchar('%', len);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	args;

	va_start(args, str);
	len = 0;
	while (*str)
	{
		if (*str == '%')
		{
			len += choices(*(str + 1), args);
			str++;
		}
		else
			len = ft_putchar(*str, len);
		str++;
	}
	return (len);
}
