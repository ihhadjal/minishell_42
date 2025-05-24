/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakambou <fakambou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:39:33 by fakambou          #+#    #+#             */
/*   Updated: 2025/05/24 19:28:31 by fakambou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	redirection_in(t_lexer *redirections)
{
	int	fd_in;
	if (redirections->token_type ==  REDIREC_IN)
	{
		fd_in = open(redirections->next->str, O_RDONLY);
		if (fd_in == -1)
		{
			perror(redirections->next->str);
			exit(EXIT_FAILURE);
		}
		if (dup2(fd_in, STDIN_FILENO) == -1)
    	{
    	perror("redirection_in");
    	exit(EXIT_FAILURE);
    	}
		close(fd_in);
	}
}

void	redirection_out(t_lexer *redirections)
{
	int	fd_out;
	if (redirections->token_type ==  REDIREC_OUT)
	{
		fd_out = open(redirections->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			perror(redirections->next->str);
			exit(EXIT_FAILURE);
		}
		else if (fd_out == 0)
			dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void	redirection_append(t_lexer *redirections)
{
	int	fd;

	if (redirections->token_type == APPEND)
	{
		fd = open(redirections->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(redirections->next->str);
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("append");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
}

void	redirections_heredoc(t_lexer *redirections)
{
	if(redirections->token_type == HEREDOC)
		printf("je l ai pas encore fait eshhhhhhhhh");
}
void	handle_redirections(t_lexer *redirections)
{
		if (redirections->token_type == REDIREC_IN)
			redirection_in(redirections);
		else if (redirections->token_type == REDIREC_OUT)
			redirection_out(redirections);
		else if (redirections->token_type == APPEND)
			redirection_append(redirections);
		else if (redirections->token_type == HEREDOC)
			redirections_heredoc(redirections);
}
