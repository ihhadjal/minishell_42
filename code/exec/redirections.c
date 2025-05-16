/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakambou <fakambou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:05:15 by fakambou          #+#    #+#             */
/*   Updated: 2025/05/16 16:31:09 by fakambou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	redirect_in(t_lexer *redirect)
{
	int		fd;
	pid_t	process;

	process = fork();
	if (redirect->token_type == REDIREC_IN)
	{
		fd = open(redirect->next->str, O_RDONLY);
		if (fd == -1)
		{
			perror(redirect->next->str);
			return;
		}
		dup2(fd, STDIN_FILENO);
		close (fd);
	}
}

void	redirect_out(t_lexer *redirect)
{
	int	fd;

	if (redirect->token_type == REDIREC_OUT)
	{
		fd = open(redirect->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
		{
			perror(redirect->next->str);
			return;
		}
		dup2(fd, STDOUT_FILENO);
		close (fd);
	}
}

void	redirections(t_lexer *redirections)
{
	if (redirections->token_type == REDIREC_IN)
		redirect_in(redirections);
	if (redirections->token_type == REDIREC_OUT)
		redirect_out(redirections);
}
