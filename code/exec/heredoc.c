/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:51:43 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/10 12:59:18 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	handle_heredoc_redirection(char *delimiter)
{
	int	pipefd[2];
	int	pid;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == 0)
		handle_heredoc_child(pipefd, delimiter);
	else if (pid > 0)
		return (handle_heredoc_parent(pipefd, pid));
	else
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	return (0);
}

void	handle_heredoc_child(int *pipefd, char *delimiter)
{
	char	*line;

	close(pipefd[0]);
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(pipefd[1]);
			exit(0);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			close(pipefd[1]);
			exit(0);
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
}

int	handle_heredoc_parent(int *pipefd, int pid)
{
	int status;

	close(pipefd[1]);
	ignore_signals();
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipefd[0]);
		return (-1);
	}
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[0]);
		perror("dup2");
		return (-1);
	}
	close(pipefd[0]);
	return (0);
}
