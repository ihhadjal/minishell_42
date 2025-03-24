/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:12:49 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/06 19:15:53 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count = ft_putstr("-2147483648");
		return (count);
	}
	else
	{
		if (n < 0)
		{
			count += ft_putchar('-');
			n = -n;
		}
		if (n > 9)
		{
			count += ft_putnbr(n / 10);
		}
		count += ft_putchar((n % 10 + '0'));
	}
	return (count);
}
