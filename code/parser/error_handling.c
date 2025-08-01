/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:02:26 by iheb              #+#    #+#             */
/*   Updated: 2025/06/11 16:06:44 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	error_handling(t_lexer *lex)
{
	if (!lex)
		return (1);
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
			return (2);
		lex = lex->next;
	}
	return (1);
}

int	handle_redirection_errors(t_lexer *lex)
{
	if ((lex->token_type == APPEND && lex->next->token_type != WORD)
		|| (lex->token_type == APPEND && lex->next->token_type == REDIREC_OUT))
		check_redirections(lex);
	else if ((lex->token_type == HEREDOC && lex->next->token_type != WORD)
		|| (lex->token_type == HEREDOC && lex->next->token_type == REDIREC_IN))
	{
		if (lex->next->token_type == REDIREC_IN)
			ft_putendl_fd("syntax error near unexpected token `<'", 2);
		else
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
			return (0);
		}
	}
	return (1);
}
