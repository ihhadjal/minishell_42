/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:20:35 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/11 16:25:10 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	check_dir(char *path, DIR *dir)
{
	if (dir != NULL)
	{
		closedir(dir);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Is a directory", 2);
		exit(126);
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

void	check_pipe_error(t_pipe_data *pipe_data, int i)
{
	if (pipe(pipe_data->pipes[i]) == -1)
	{
		perror("pipe");
		cleanup_pipes(pipe_data->pipes, i);
		exit(1);
	}
}

int	export_and_unset(t_parser_commands *current, int i,
		t_environnement *mini_env)
{
	if (!ft_strcmp(current->cmd_str[i], "export"))
		return (parsarg_export(&current->cmd_str[i], mini_env));
	if (!ft_strcmp(current->cmd_str[i], "unset"))
		return (parsarg_unset(&current->cmd_str[i], mini_env));
	return (0);
}

void	check_newline(int newline)
{
	if (newline)
		ft_putchar_fd('\n', 1);
}
