/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:57:56 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/01 12:58:26 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	print_list(t_lexer *lex)
{
	char *token_names[] = {"WORD", "PIPE", "REDIREC_IN", "REDIREC_OUT",
		"APPEND", "HEREDOC"};
	while (lex)
	{
		printf("token str: %s, token type: %s\n", lex->str,
			token_names[lex->token_type]);
		lex = lex->next;
	}
}