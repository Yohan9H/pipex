/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:26:56 by yohan.h           #+#    #+#             */
/*   Updated: 2024/06/21 15:12:43 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

static int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

static int	nb_base(long nb, char *base, int size_b)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
		i++;
	}
	if (nb >= size_b)
	{
		i += nb_base(nb / size_b, base, size_b);
	}
	ft_putchar(base[nb % size_b]);
	i++;
	return (i);
}

static int	which_ways(char ways, va_list ap)
{
	if (ways == 'c')
		return (ft_putchar(va_arg(ap, int)));
	if (ways == 's')
		return (ft_putstr(va_arg(ap, char *)));
	if (ways == 'p')
	{
		return (verif_nil(va_arg(ap, unsigned long), "0123456789abcdef", 16));
	}
	if (ways == 'd' || ways == 'i')
		return (nb_base(va_arg(ap, int), "0123456789", 10));
	if (ways == 'u')
		return (nb_base(va_arg(ap, unsigned int), "0123456789", 10));
	if (ways == 'x')
		return (nb_base(va_arg(ap, unsigned int), "0123456789abcdef", 16));
	if (ways == 'X')
		return (nb_base(va_arg(ap, unsigned int), "0123456789ABCDEF", 16));
	if (ways == '%')
	{
		ft_putchar('%');
		return (1);
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	size_t	i;
	va_list	ap;
	int		nb_print;

	nb_print = 0;
	i = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			nb_print += which_ways(format[i + 1], ap);
			i++;
		}
		else
		{
			ft_putchar(format[i]);
			nb_print++;
		}
		i++;
	}
	va_end(ap);
	return (nb_print);
}

// #include <stdio.h>
// int	main()
// {
// 	printf("%s %d\n", "salut");
// 	//ft_printf("%s %d\n", "salut");
// }