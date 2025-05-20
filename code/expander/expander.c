/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:17:36 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/20 13:09:00 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	expand_commands(t_lexer *lex, t_environnement *mini_env)
{
	char	*expanded_variable;

	(void)expanded_variable;
	while (lex)
	{
		if (expansion_checker(lex->str) == 1)
		{
			expanded_variable = expand_variable_value(lex->str, mini_env);
		}
		lex = lex->next;
	}
}
char	*expand_variable_value(char *str, t_environnement *mini_env)
{
	int				var_len;
	char			*var_name;
	t_environnement	*current;

	current = mini_env;
	while (current)
	{
		var_len = ft_strlen(current->variable_name);
		var_name = ft_substr(current->variable_name, 0, var_len - 1);
		if (ft_strcmp(str + 1, var_name) == 0)
			return (current->variable_value);
		current = current->next;
	}
	return (NULL);
}

int	expansion_checker(char *str)
{
	int i;
	int single_quote;

	single_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			single_quote = 1;
		else if (single_quote == 0)
		{
			if (str[i] == '$')
				return (1);
		}
		i++;
	}
	return (0);
}