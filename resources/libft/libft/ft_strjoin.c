/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:56:10 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/06 19:09:15 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		c;
	char	*result;

	i = 0;
	c = 0;
	if (!s1 || !s2)
		return (0);
	result = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (0);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[c])
	{
		result[i] = s2[c];
		i++;
		c++;
	}
	result[i] = '\0';
	return (result);
}

// int main(void)
// {
// 	char s1[] = "iheb ";
// 	char s2[] = "le tunisien";
// 	char *res = ft_strjoin(s1, s2);
// 	printf("%s", res);
// 	free (res);
// 	return 0;
// }