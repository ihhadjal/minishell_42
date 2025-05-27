/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:46:18 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/27 15:40:03 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	builtin(t_lexer *builtin, t_environnement *mini_env, t_mini *mini)
{
	t_lexer	*current;
	int		command_found;
	int		exit_status;

	current = builtin;
	command_found = 0;
	exit_status = 0;
	while (current)
	{
		if (check_if_builtin(current, command_found) == 1)
		{
			exit_status = execute_builtins(current, mini_env, mini);
			command_found = 1;
		}
		current = current->next;
	}
	exit_status = is_not_builtin_command(builtin, command_found);
	return (exit_status);
}

int	is_not_builtin_command(t_lexer *builtin, int command_found)
{
	if (!command_found && builtin && builtin->token_type == WORD)
	{
		if (ft_strchr(builtin->str, '/'))
		{
			print_error(builtin->str, ": Is a directory");
			return (126);
		}
		else
		{
			print_error(builtin->str, ": command not found");
			return (127);
		}
	}
	return (0);
}

int	execute_builtins(t_lexer *current, t_environnement *mini_env, t_mini *mini)
{
	while (current)
	{
		if (current->token_type >= ECHO && current->token_type <= UNSET)
			return (dispatch_builtin(current, mini_env, mini));
		current = current->next;
	}
	return (1);
}

int	handle_unset_builtin(t_lexer *builtin, t_environnement *mini_env)
{
	if (builtin->token_type == UNSET)
	{
		while (builtin->next)
		{
			delete_node(builtin, &mini_env);
			builtin = builtin->next;
		}
		return (0);
	}
	else
		return (1);
}

void	delete_node(t_lexer *builtin, t_environnement **mini_env)
{
	t_environnement	*current;
	t_environnement	*prev;
	int				var_len;
	char			*var_name;

	current = *mini_env;
	prev = NULL;
	while (current)
	{
		var_len = ft_strlen(current->variable_name);
		var_name = ft_substr(current->variable_name, 0, var_len - 1);
		if (var_name && ft_strcmp(var_name, builtin->next->str) == 0)
		{
			if (prev)
				prev->next = NULL;
			else
				*mini_env = current->next;
			free_node(var_name, current);
			return ;
		}
		free(var_name);
		prev = current;
		current = current->next;
	}
}
