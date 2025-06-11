/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:47:08 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/27 15:57:13 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	count_new_len(char *str)
{
	int	new_len;
	int	i;

	i = 0;
	new_len = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			new_len++;
		i++;
	}
	return (new_len);
}

char	*handle_dollar_quote(char *str)
{
	int		i;
	char	*result;
	int		start;
	int		end;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '\'')
		{
			start = i + 2;
			end = start;
			while (str[end] && str[end] != '\'')
				end++;
			if (str[end] == '\'')
			{
				result = ft_substr(str, start, end - start);
				return (result);
			}
		}
		i++;
	}
	return (NULL);
}

void	process_quote(char c, t_mini *mini, char *new_str, int *j)
{
	if (c == '"')
	{
		if (mini->in_single)
			new_str[(*j)++] = c;
		else
			mini->in_double = !(mini->in_double);
	}
	else if (c == '\'')
	{
		if (mini->in_double)
			new_str[(*j)++] = c;
		else
			mini->in_single = !(mini->in_single);
	}
	else
		new_str[(*j)++] = c;
}
