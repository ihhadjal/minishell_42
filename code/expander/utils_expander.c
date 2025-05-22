/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:00:00 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/22 12:00:11 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (0);
}
int	expansion_checker(char *str)
{
	int	i;
	int	single_quote;

	single_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			single_quote = !single_quote;
		else if (single_quote == 0)
		{
			if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i
					+ 1] == '_'))
				return (1);
		}
		i++;
	}
	return (0);
}

int	find_var_end(char *str, int start)
{
	int i = start;

	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i - 1);
}