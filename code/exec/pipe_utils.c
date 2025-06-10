/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:48:10 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/10 13:00:21 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	execute_child_process(t_parser_commands *cmd, t_environnement *mini_env,
		int **pipes, int cmd_index)
{
	setup_child_signals();
	setup_pipe_redirections(pipes, cmd_index);
	close_all_pipes(pipes);
	if (setup_redirections(cmd) == -1)
		exit(1);
	if (is_builtin_command(cmd))
		exit(execute_builtin_in_pipe(cmd, mini_env));
	else
		execute_external_in_pipe(cmd, mini_env);
}

void	setup_pipe_redirections(int **pipes, int cmd_index)
{
	if (cmd_index > 0)
	{
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	}
	if (pipes[cmd_index])
	{
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	}
}

void	close_all_pipes(int **pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	execute_builtin_in_pipe(t_parser_commands *cmd, t_environnement *mini_env)
{
	t_mini	mini;

	ft_memset(&mini, 0, sizeof(t_mini));
	return (execute_parsarg_builtins(cmd, mini_env, &mini));
}

void	execute_external_in_pipe(t_parser_commands *cmd, t_environnement *mini_env)
{
	char **env_array;
	char *path;

	env_array = env_to_array(mini_env);
	path = find_command_path(cmd->cmd_str[0], mini_env);
	if (!path)
	{
		ft_putstr_fd(cmd->cmd_str[0], 2);
		ft_putendl_fd(": command not found", 2);
		free_env_array(env_array);
		exit(127);
	}
	execve(path, cmd->cmd_str, env_array);
	perror("execve");
	free(path);
	free_env_array(env_array);
	exit(1);
}
