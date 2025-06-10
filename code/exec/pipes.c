/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:26:23 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/10 13:02:11 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	execute_pipe_chain(t_parser_commands *pars, t_environnement *mini_env,
		int cmd_count)
{
	int	**pipes;
	int	*pids;
	int	exit_status;

	pipes = create_pipes(cmd_count - 1);
	if (!pipes)
		return (1);
	pids = malloc(sizeof(int) * cmd_count);
	if (!pids)
	{
		cleanup_pipes(pipes, cmd_count - 1);
		return (1);
	}
	execute_pipe_processes(pars, mini_env, pipes, pids);
	cleanup_pipes(pipes, cmd_count - 1);
	exit_status = wait_for_children(pids, cmd_count);
	free(pids);
	return (exit_status);
}

int	**create_pipes(int pipe_count)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * pipe_count);
	if (!pipes)
		return (NULL);
	while (i < pipe_count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			cleanup_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	cleanup_pipes(int **pipes, int pipe_count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
		}
		i++;
	}
	free(pipes);
}

void	execute_pipe_processes(t_parser_commands *pars,
		t_environnement *mini_env, int **pipes, int *pids)
{
	t_parser_commands	*current;
	int					i;

	i = 0;
	current = pars;
	while (current)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			execute_child_process(current, mini_env, pipes, i);
		current = current->next;
		i++;
	}
}

int	wait_for_children(int *pids, int cmd_count)
{
	int	status;
	int	exit_status;
	int	i;

	exit_status = 0;
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (exit_status);
}
