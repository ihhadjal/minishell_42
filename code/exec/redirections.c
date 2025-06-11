/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iheb <iheb@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:51:08 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/10 21:49:26 by iheb             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	setup_redirections(t_parser_commands *cmd)
{
	t_lexer	*redir;

	if (!cmd->redirections)
		return (0);
	redir = cmd->redirections;
	while (redir)
	{
		if (handle_single_redirection(redir) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

int	handle_single_redirection(t_lexer *redir)
{
	if (redir->token_type == REDIREC_IN)
		return (handle_input_redirection(redir->str));
	else if (redir->token_type == REDIREC_OUT)
		return (handle_output_redirection(redir->str));
	else if (redir->token_type == APPEND)
		return (handle_append_redirection(redir->str));
	else if (redir->token_type == HEREDOC)
		return (handle_heredoc_redirection(redir->str));
	return (0);
}

int	handle_input_redirection(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_output_redirection(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_append_redirection(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}
