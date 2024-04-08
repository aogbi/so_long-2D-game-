/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:27:15 by aogbi             #+#    #+#             */
/*   Updated: 2023/12/05 15:29:55 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);

size_t	ft_strlen(const char *s);

int		ft_putchar(char c, int len);

int		ft_putstr(char *s, int len);

int		ft_putnbr_base(long nbr, char *base, int len);

int		ft_putbase(size_t nbr, char *base, int len);

#endif
