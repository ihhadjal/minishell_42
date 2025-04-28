/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:01:42 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/28 15:08:35 by ihhadjal         ###   ########.fr       */
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

void	free_parser_list(t_parser_commands *parse)
{
	t_parser_commands *tmp;

	while (parse)
	{
		tmp = parse->next;
		free(parse->cmd_str);
		free(parse->hd_file_name);
		free(parse->redirections);
		free(tmp);
		parse = tmp;
	}
}