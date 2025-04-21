/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:57:56 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/21 15:03:07 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	print_list(t_lexer *lex)
{
	char	*token_names[] = {"WORD", "PIPE", "REDIREC_IN", "REDIREC_OUT",
			"APPEND", "HEREDOC", "ECHO", "CD", "PWD", "EXPORT", "UNSET", "ENV",
			"EXIT"};

	while (lex)
	{
		printf("token str: %s, token type: %s\n", lex->str,
			token_names[lex->token_type]);
		lex = lex->next;
	}
}

void	quotes_loop(char **str, t_mini *mini)
{
	while (!check_quotes(*str))
	{
		mini->tmp = *str;
		mini->str1 = readline("> ");
		*str = ft_strjoin(*str, mini->str1);
		free(mini->str1);
		free(mini->tmp);
	}
}

void	builtin_tokens(char *str, t_lexer *lexer)
{
	if (!ft_strncmp(str, "echo", 4) && is_sep(str[4]))
	{
		lexer->str = ft_strdup("echo");
		lexer->token_type = ECHO;
	}
	else if (!ft_strncmp(str, "cd", 2) && is_sep(str[2]))
	{
		lexer->str = ft_strdup("cd");
		lexer->token_type = CD;
	}
	else if (!ft_strncmp(str, "pwd", 3) && is_sep(str[3]))
	{
		lexer->str = ft_strdup("pwd");
		lexer->token_type = PWD;
	}
	else if (!ft_strncmp(str, "export", 6) && is_sep(str[6]))
	{
		lexer->str = ft_strdup("export");
		lexer->token_type = EXPORT;
	}
	else if (!ft_strncmp(str, "unset", 5) && is_sep(str[5]))
	{
		lexer->str = ft_strdup("unset");
		lexer->token_type = UNSET;
	}
}

void	free_all(char *str, t_lexer *lex)
{
	free(str);
	free_lexer_list(lex);
}
