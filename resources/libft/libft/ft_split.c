/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:54:08 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/06 19:09:15 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	ft_count_word(char const *s, char sep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == sep && s[i])
			i++;
		if (s[i])
			j++;
		while (s[i] != sep && s[i])
			i++;
	}
	return (j);
}

static char	*ft_cpy(char **res, const char *s, char sep)
{
	int	len;

	while (*s)
	{
		len = 0;
		while (*s == sep && *s)
			s++;
		while (*s != sep && *s)
		{
			len++;
			s++;
		}
		if (len > 0)
		{
			*res = malloc(len + 1);
			if (*res == NULL)
				return (NULL);
			ft_strlcpy(*res, s - len, len + 1);
			res++;
		}
	}
	return (*res);
}

char	**ft_split(char const *s, char c)
{
	int		mots;
	char	**res;

	if (!s)
		return (NULL);
	mots = ft_count_word(s, c);
	res = malloc(sizeof(char *) * (mots + 1));
	if (!res)
		return (NULL);
	res[mots] = NULL;
	ft_cpy(res, s, c);
	return (res);
}

// int main (void)
// {
// 	char *s = "  salut iheb comment ca va        ";
// 	char **res = ft_split(s, ' ');
// 	while (*res)
// 	{
// 		printf("%s\n", *res);
// 		res++;
// 	}
// }