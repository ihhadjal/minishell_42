/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:26:23 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/11 15:43:12 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	execute_pipe_chain(t_parser_commands *pars, t_environnement *mini_env,
		int cmd_count)
{
	t_pipe_data	pipe_data;
	int			exit_status;

	pipe_data.pipes = create_pipes(cmd_count - 1);
	if (!pipe_data.pipes)
		return (1);
	pipe_data.pids = malloc(sizeof(int) * cmd_count);
	if (!pipe_data.pids)
	{
		cleanup_pipes(pipe_data.pipes, cmd_count - 1);
		return (1);
	}
	pipe_data.cmd_count = cmd_count;
	execute_pipe_processes(pars, mini_env, &pipe_data, cmd_count);
	cleanup_pipes(pipe_data.pipes, cmd_count - 1);
	exit_status = wait_for_children(pipe_data.pids, cmd_count);
	free(pipe_data.pids);
	return (exit_status);
}

int	**create_pipes(int pipe_count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (pipe_count + 1));
	if (!pipes)
		return (NULL);
	i = 0;
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
	pipes[pipe_count] = NULL;
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
		t_environnement *mini_env, t_pipe_data *pipe_data, int cmd_count)
{
	t_parser_commands	*current;
	int					i;

	i = 0;
	while (i < cmd_count - 1)
	{
		check_pipe_error(pipe_data, i);
		i++;
	}
	i = 0;
	current = pars;
	while (current)
	{
		pipe_data->pids[i] = fork();
		if (pipe_data->pids[i] == 0)
			execute_child_process(current, mini_env, pipe_data->pipes, i);
		else if (pipe_data->pids[i] < 0)
		{
			perror("fork");
			exit(1);
		}
		current = current->next;
		i++;
	}
	close_all_pipes_in_parent(pipe_data->pipes, cmd_count - 1);
}

void	close_all_pipes_in_parent(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}
