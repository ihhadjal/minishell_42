/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:26:23 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/11 14:28:13 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	execute_commands(t_parser_commands *pars, t_environnement *mini_env,
		t_mini *mini)
{
	int	exit_status;

	if (!pars)
		return (0);
	exit_status = execute_pipeline(pars, mini_env, mini);
	return (exit_status);
}

int	execute_pipeline(t_parser_commands *pars, t_environnement *mini_env,
		t_mini *mini)
{
	int	cmd_count;

	cmd_count = count_commands(pars);
	if (cmd_count == 1)
		return (execute_single_command(pars, mini_env, mini));
	else
		return (execute_pipe_chain(pars, mini_env, cmd_count));
}

int	count_commands(t_parser_commands *pars)
{
	int					count;
	t_parser_commands	*current;

	count = 0;
	current = pars;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	execute_single_command(t_parser_commands *cmd, t_environnement *mini_env, t_mini *mini)
{
    int status_code;
    int original_stdin;
    int original_stdout;

    original_stdin = dup(STDIN_FILENO);
    original_stdout = dup(STDOUT_FILENO);
    
    if (setup_redirections(cmd) == -1)
    {
        restore_stdio(original_stdin, original_stdout);
        return (1);
    }
    if (cmd->cmd_str == NULL || cmd->cmd_str[0] == NULL || 
        ft_strlen(cmd->cmd_str[0]) == 0)
    {
        restore_stdio(original_stdin, original_stdout);
        return (0);
    }
    if (is_builtin_command(cmd))
        status_code = execute_parsarg_builtins(cmd, mini_env, mini);
    else
        status_code = execute_external_command(cmd, mini_env);
    restore_stdio(original_stdin, original_stdout);
    return (status_code);
}


int	is_builtin_command(t_parser_commands *cmd)
{
	if (!cmd || !cmd->cmd_str || !cmd->cmd_str[0])
		return (0);
	if (ft_strcmp(cmd->cmd_str[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_str[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_str[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_str[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_str[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_str[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd_str[0], "exit") == 0)
		return (1);
	return (0);
}
