/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:18:17 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/18 19:14:53 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

t_parser_commands	*parser(t_lexer *lexer, t_mini *mini)
{
	mini->first_cmd = NULL;
	mini->cmd_parser = NULL;
	mini->current_token = lexer;
	while (mini->current_token)
	{
		mini->new_cmd = malloc(sizeof(t_parser_commands));
		if (!mini->new_cmd)
			exit(1);
		init_new_cmd(mini);
		if (!mini->first_cmd)
			mini->first_cmd = mini->new_cmd;
		if (mini->cmd_parser)
		{
			mini->cmd_parser->next = mini->new_cmd;
			mini->new_cmd->prev = mini->cmd_parser;
		}
		mini->cmd_parser = mini->new_cmd;
		if (mini->current_token && mini->current_token->token_type == PIPE)
			mini->current_token = mini->current_token->next;
		mini->current_token = mini->current_token->next;
	}
	return (mini->first_cmd);
}
