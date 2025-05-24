/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:46:18 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/24 15:16:45 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	builtin(t_lexer *builtin, t_environnement *mini_env)
{
	t_lexer *current;
    int command_found;
	int	exit_status;
    
	current = builtin;
	command_found = 0;
	exit_status = 0;
    while (current)
    {
		if (check_if_builtin(current, command_found) == 1)
			exit_status = execute_builtins(current, mini_env);
        current = current->next;
    }
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
		return (0);
	}
    return (exit_status);
}

int	execute_builtins(t_lexer *current, t_environnement *mini_env)
{
	while (current)
	{
		if (current->token_type == ECHO)
		{
			return(put_echo(current));
			break;
		}
		else if (current->token_type == CD)
		{
			return (cd(current));
			break;
		}
		else if (current->token_type == PWD)
			return get_pwd();
		else if (current->token_type == EXIT)
			ft_exit(current);
		else if (current->token_type == EXPORT)
			return (export_builtin(current, mini_env));
		else if (current->token_type == ENV)
		{
			print_env(mini_env);
			return (0);
		}
		else if (current->token_type == UNSET)
			return handle_unset_builtin(current, mini_env);
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

void	free_node(char *var_name, t_environnement *current)
{
	free(var_name);
	free(current->variable_name);
	free(current->variable_value);
	free(current);
}
