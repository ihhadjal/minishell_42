/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:17:36 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/11 13:19:55 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	expand_commands(t_lexer *lex, t_environnement *mini_env,
		t_expander *exp, t_mini *mini)
{
	char	*dollar_quote_str;

	exp->current = lex;
	while (exp->current)
	{
		handle_special_cases(exp->current, mini);
		dollar_quote_str = handle_dollar_quote(exp->current->str);
		if (dollar_quote_str)
		{
			free(exp->current->str);
			exp->current->str = dollar_quote_str;
		}
		else
		{
			while (expansion_checker(exp->current->str) == 1)
				expansion_logic(exp, mini_env);
		}
		if (exp->current->token_type != HEREDOC)
		{
			exp->old_str = exp->current->str;
			exp->current->str = remove_quotes(exp->old_str, mini);
			free(exp->old_str);
		}
		exp->current = exp->current->next;
	}
}

void	expansion_logic(t_expander *exp, t_environnement *mini_env)
{
	exp->expanded_variable = expand_variable_value(exp->current->str, mini_env,
			exp);
	exp->start = find_dollar(exp->current->str);
	exp->end = find_var_end(exp->current->str, exp->start + 1);
	if (exp->expanded_variable)
	{
		substitution(exp->current, exp->start, exp->end,
			exp->expanded_variable);
		free(exp->expanded_variable);
	}
	else
		substitution(exp->current, exp->start, exp->end, "");
}

void	substitution(t_lexer *current, int start_index, int end_index,
		char *expanded_variable)
{
	int		total_length;
	int		prefix_len;
	int		suffix_len;
	char	*new_str;

	prefix_len = start_index;
	suffix_len = ft_strlen(current->str) - end_index - 1;
	total_length = prefix_len + ft_strlen(expanded_variable) + suffix_len;
	new_str = malloc(sizeof(char) * (total_length + 1));
	if (!new_str)
		return ;
	ft_strncpy(new_str, current->str, prefix_len);
	new_str[prefix_len] = '\0';
	ft_strcat(new_str, expanded_variable);
	ft_strcat(new_str, current->str + end_index + 1);
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
	exp->current1 = mini_env;
	while (exp->current1)
	{
		exp->env_name = ft_substr(exp->current1->variable_name, 0,
				ft_strlen(exp->current1->variable_name) - 1);
		if (ft_strcmp(exp->var_name, exp->env_name) == 0)
		{
			free(exp->var_name);
			free(exp->env_name);
			return (exp->current1->variable_value);
		}
		free(exp->env_name);
		exp->current1 = exp->current1->next;
	}
	free(exp->var_name);
	return (NULL);
}
