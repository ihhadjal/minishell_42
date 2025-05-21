/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:17:36 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/21 18:47:26 by ihhadjal         ###   ########.fr       */
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
			if (expanded_variable)
				printf("%s\n", expanded_variable);
			else
				printf("ca marche pas bekhe\n");
		}
		lex = lex->next;
	}
}
char	*expand_variable_value(char *str, t_environnement *mini_env)
{
	int	i;
	t_environnement *current;
	int				var_len;
	char			*var_name;
	
	current = mini_env;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			while (current)
			{
				var_len = ft_strlen(current->variable_name);
				var_name = ft_substr(current->variable_name, 0, var_len - 1);
				if (ft_strcmp(ft_substr(str, find_dollar(str) + 1, ft_strlen(str)), var_name) == 0)
					return (current->variable_value);
				current = current->next;
			}
		}
		i++;
	}
	return (NULL);
}
int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return i;
		i++;
	}
	return i;
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