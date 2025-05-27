/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:01:42 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/27 14:58:45 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	builtin_tokens2(char *str, t_lexer *lexer)
{
	if (!ft_strncmp(str, "env", 3) && is_sep(str[3]))
	{
		lexer->str = ft_strdup("env");
		lexer->token_type = ENV;
	}
	else if (!ft_strncmp(str, "exit", 4) && is_sep(str[4]))
	{
		lexer->str = ft_strdup("exit");
		lexer->token_type = EXIT;
	}
}

int	fake_redirec_token(char *str, t_lexer *token)
{
	if (str[0] == '<')
	{
		if (str[1] == '>')
		{
			token->str = ft_strdup("<>");
			token->token_type = FAKE_REDIREC;
			return (0);
		}
	}
	else if (str[0] == '>')
	{
		if (str[1] == '<')
		{
			token->str = ft_strdup("><");
			token->token_type = FAKE_REDIREC2;
			return (0);
		}
	}
	return (1);
}
