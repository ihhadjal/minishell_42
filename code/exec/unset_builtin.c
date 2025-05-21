/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iheb <iheb@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:46:18 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/21 10:28:17 by iheb             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	builtin(t_lexer *builtin, t_environnement *mini_env)
{
	t_lexer *current;
    int command_found;
    
	current = builtin;
	command_found = 0;
    while (current)
    {
		if (check_if_builtin(current, command_found) == 1)
			execute_builtins(current, mini_env);
        current = current->next;
    }
    if (!command_found && builtin && builtin->token_type == WORD)
    {
        ft_putstr_fd(builtin->str, 2);
        ft_putendl_fd(": command not found", 2);
        return (127); 
	}
    return (0);
}

void	execute_builtins(t_lexer *current, t_environnement *mini_env)
{
	while (current)
	{
		if (current->token_type == ECHO)
		{
			put_echo(current);
			break;
		}
		else if (current->token_type == CD)
		{
			cd(current);
			break;
		}
		else if (current->token_type == PWD)
			get_pwd();
		else if (current->token_type == EXIT)
			ft_exit(current);
		else if (current->token_type == EXPORT)
			export_builtin(current, mini_env);
		else if (current->token_type == ENV)
			print_env(mini_env);
		else if (current->token_type == UNSET)
			handle_unset_builtin(current, mini_env);
		current = current->next;
	}
}

void	handle_unset_builtin(t_lexer *builtin, t_environnement *mini_env)
{
	if (builtin->token_type == UNSET && builtin->next)
	{
		while (builtin->next)
		{
			delete_node(builtin, &mini_env);
			builtin = builtin->next;
		}
	}
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
