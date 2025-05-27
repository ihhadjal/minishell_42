/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:00:00 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/27 15:53:44 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	find_dollar(char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (str[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if (str[i] == '$' && !single_quote)
			return (i);
		i++;
	}
	return (-1);
}

int	expansion_checker(char *str)
{
	int	i;
	int	single_quote;

	i = 0;
	single_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			single_quote = !single_quote;
		else if (str[i] == '$' && str[i + 1] && str[i + 1] == '\'')
			i++;
		else if (single_quote == 0 && str[i] == '$' && str[i + 1]
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			return (1);
		i++;
	}
	return (0);
}

int	find_var_end(char *str, int start)
{
	int	i;

	i = start;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i - 1);
}

void	handle_special_cases(t_lexer *lex, t_mini *mini)
{
	int		i;
	t_lexer	*current;
	int		single_quote;
	int		double_quote;
	char	*exit_status;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	current = lex;
	while (current->str[i])
	{
		if (current->str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (current->str[i] == '"' && !single_quote)
			double_quote = !double_quote;
		if (current->str[i] == '$' && current->str[i + 1] == '?'
			&& single_quote == 0)
		{
			exit_status = ft_itoa(mini->last_exit_status);
			substitution(current, i, i + 1, exit_status);
			free(exit_status);
		}
		i++;
	}
}

char	*remove_quotes(char *str, t_mini *mini)
{
	int		i;
	int		j;
	int		new_len;
	char	*new_str;

	if (!str)
		return (NULL);
	new_len = count_new_len(str);
	new_str = malloc(sizeof(char) * (new_len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	mini->in_single = 0;
	mini->in_double = 0;
	while (str[i])
	{
		process_quote(str[i], mini, new_str, &j);
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
