/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:14:00 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/06 19:15:53 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

int	ft_uputnbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
	{
		count += ft_uputnbr(n / 10);
	}
	count += ft_putchar((n % 10 + '0'));
	return (count);
}
