/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:17:36 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/22 11:59:49 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	expand_commands(t_lexer *lex, t_environnement *mini_env,
		t_expander *exp)
{
	char	*expanded_variable;
	int		start;
	int		end;
	t_lexer	*current;

	current = lex;
	while (current)
	{
		if (expansion_checker(current->str) == 1)
		{
			expanded_variable = expand_variable_value(current->str, mini_env,
					exp);
			if (expanded_variable)
			{
				start = find_dollar(current->str);
				end = find_var_end(current->str, start + 1);
				substitution(current, current->str, start, end,
					expanded_variable);
			}
			printf("%s\n", current->str);
		}
		current = current->next;
	}
}

void	substitution(t_lexer *current, char *str, int start_index,
		int end_index, char *expanded_variable)
{
	int		total_length;
	int		prefix_len;
	int		suffix_len;
	char	*new_str;

	prefix_len = start_index;
	suffix_len = ft_strlen(str) - end_index - 1;
	total_length = prefix_len + ft_strlen(expanded_variable) + suffix_len;
	new_str = malloc(sizeof(char) * (total_length + 1));
	if (!new_str)
		return ;
	ft_strncpy(new_str, str, prefix_len);
	new_str[prefix_len] = '\0';
	ft_strcat(new_str, expanded_variable);
	ft_strcat(new_str, str + end_index + 1);
	free(current->str);
	current->str = new_str;
}
char	*expand_variable_value(char *str, t_environnement *mini_env,
		t_expander *exp)
{
	exp->dollar_pos = find_dollar(str);
	if (exp->dollar_pos == -1 || str[exp->dollar_pos + 1] == '\0')
		return (NULL);
	exp->var_end = find_var_end(str, exp->dollar_pos + 1);
	exp->var_len = exp->var_end - exp->dollar_pos;
	exp->var_name = ft_substr(str, exp->dollar_pos + 1, exp->var_len);
	if (!exp->var_name)
		return (NULL);
	exp->current = mini_env;
	while (exp->current)
	{
		exp->env_name = ft_substr(exp->current->variable_name, 0,
				ft_strlen(exp->current->variable_name) - 1);
		if (ft_strcmp(exp->var_name, exp->env_name) == 0)
		{
			free(exp->var_name);
			free(exp->env_name);
			return (exp->current->variable_value);
		}
		free(exp->env_name);
		exp->current = exp->current->next;
	}
	free(exp->var_name);
	return (NULL);
}
