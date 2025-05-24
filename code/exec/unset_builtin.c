/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakambou <fakambou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:46:18 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/24 15:40:42 by fakambou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"


void	builtin(t_lexer *builtin, t_environnement *mini_env)
{
	while (builtin)
	{
		if ((builtin->token_type == ECHO))
		{
			put_echo(builtin);
			break ;
		}
		else if (builtin->token_type == CD)
		{
			cd(builtin);
			break ;
		}
		else if (builtin->token_type == PWD)
			get_pwd();
		else if (builtin->token_type == EXIT)
			ft_exit(builtin);
		else if (builtin->token_type == EXPORT)
		{
			export_builtin(builtin, mini_env);
		}
		else if (!ft_strncmp(builtin->str, "env", 3) && is_sep(builtin->str[3]))
			print_env(mini_env);
		handle_unset_builtin(builtin, mini_env);
		builtin = builtin->next;
	}
}
void	handle_unset_builtin(t_lexer *builtin, t_environnement *mini_env)
{
	if (builtin->token_type == UNSET && builtin->next->token_type == WORD)
	{
		delete_node(builtin, &mini_env);
	}
}

void	delete_node(t_lexer *builtin, t_environnement **mini_env)
{
	t_environnement *current;
	t_environnement	*prev;
	int				var_len;
	char			*var_name;

	current = *mini_env;
	prev = NULL;
	while (current)
	{
		var_len = ft_strlen (current->variable_name);
		var_name = ft_substr (current->variable_name, 0, var_len - 1);
		if (var_name && ft_strcmp(var_name, builtin->next->str) == 0)
		{
			if (prev)
				prev->next = NULL;
			else
				*mini_env = current->next;
			free_node(var_name, current);
			return;
		}
		free(var_name);
		prev = current;
		current = current->next;
	}
}

void free_node(char *var_name, t_environnement *current)
{
	free(var_name);
	free(current->variable_name);
	free(current->variable_value);
	free(current);
}
