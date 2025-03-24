/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:11:40 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/06 19:15:02 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

static int	ft_format(va_list args, const char str)
{
	int	count;

	count = 0;
	if (str == 'd' || str == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (str == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (str == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (str == 'u')
		count += ft_uputnbr(va_arg(args, unsigned int));
	else if (str == 'x' || str == 'X')
		count += ft_puthex(va_arg(args, unsigned int), str == 'X');
	else if (str == 'p')
		count += ft_putptr(va_arg(args, void *));
	else if (str == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			count;
	int			i;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += ft_format(args, str[i + 1]);
			i++;
		}
		else
			count += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
