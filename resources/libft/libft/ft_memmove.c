/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:49:57 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/06 19:09:15 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*from;

	if (!dest && !src)
		return (NULL);
	dst = dest;
	from = src;
	if (dst < from)
	{
		while (n--)
			*dst++ = *from++;
	}
	else
	{
		while (n--)
			dst[n] = from[n];
	}
	return (dest);
}

// int main(void)
// {
// 	char dest[] = "iheb";
// 	char src[] = "crack";

// 	printf ("%s", (char *)ft_memmove(dest, src, 10));
// 	return 0;
// }