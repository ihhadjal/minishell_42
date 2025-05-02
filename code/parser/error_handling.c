/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:02:26 by iheb              #+#    #+#             */
/*   Updated: 2025/05/02 17:01:30 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	error_handling(t_lexer *lex)
{
	while (lex)
	{
		if (lex->next)
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
		printf("%s\n", APPEND_ERROR);
		return (0);
	}
	else if (lex->token_type == HEREDOC && lex->next->token_type != WORD)
	{
		printf("%s\n", HEREDOC_ERROR);
		return (0);
	}
	else if (lex->token_type == REDIREC_IN && lex->next->token_type != WORD)
	{
		printf("%s\n", "syntax error near unexpected token `<'");
		return (0);
	}
	else if (lex->token_type == REDIREC_OUT && lex->next->token_type != WORD)
	{
		printf("%s\n", "syntax error near unexpected token `>'");
		return (0);
	}
	return (1);
}

int	handle_redirection_errors2(t_lexer *lex)
{
	if (lex->token_type == PIPE)
	{
		if (!lex->next)
			printf("%s\n", "syntax error near unexpected token `|'");
		else if (lex->next->token_type == PIPE)
			printf("%s\n", "syntax error near unexpected token `||'");
		else if (lex->str[0] == '|')
			printf("%s\n", "syntax error near unexpected token `|'");
		return (0);
	}
	return (1);
}
