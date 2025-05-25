/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iheb <iheb@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:02:26 by iheb              #+#    #+#             */
/*   Updated: 2025/05/25 12:01:06 by iheb             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	error_handling(t_lexer *lex)
{
	if (lex->token_type == PIPE)
	{
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
		return (2);
	}
	while (lex)
	{
		if (lex->token_type == FAKE_REDIREC || lex->token_type == FAKE_REDIREC2)
		{
			ft_putendl_fd("syntax error near unexpected token `newline'", 2);
			return (0);
		}
		else if (lex->next && lex->token_type != WORD)
		{
			if (handle_redirection_errors(lex) == 0)
				return (0);
		}
		if (handle_redirection_errors2(lex) == 0)
			return (0);
		lex = lex->next;
	}
	return (1);
}
int	handle_redirection_errors(t_lexer *lex)
{
	if (lex->token_type == APPEND && lex->next->token_type != WORD)
	{
		ft_putendl_fd("syntax error near unexpected token `>>'", 2);
		return (0);
	}
	else if (lex->token_type == HEREDOC && lex->next->token_type != WORD)
	{
		ft_putendl_fd("syntax error near unexpected token `<<'", 2);
		return (0);
	}
	else if (lex->token_type == REDIREC_IN && lex->next->token_type != WORD)
	{
		ft_putendl_fd("syntax error near unexpected token `<'", 2);
		return (0);
	}
	else if (lex->token_type == REDIREC_OUT && lex->next->token_type != WORD)
	{
		ft_putendl_fd("syntax error near unexpected token `>'", 2);
		return (0);
	}
	return (1);
}

int	handle_redirection_errors2(t_lexer *lex)
{
	if (lex->token_type == PIPE)
	{
		if (!lex->next)
		{
			ft_putendl_fd("syntax error near unexpected token `|'", 2);
			return 0;
		}
	}
	return (1);
}
