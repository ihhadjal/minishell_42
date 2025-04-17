/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:18:17 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/16 19:27:42 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

t_parser_commands	*parser(t_lexer *lexer, t_mini *mini)
{
	while (lexer)
	{
		pipe_handler(lexer, mini);
		redirections_handler(lexer, mini);
		lexer = lexer->next;
	}
	return (mini->cmd_list);
}
void	pipe_handler(t_lexer *lexer, t_mini *mini)
{
	mini->cmd_list = NULL;
	mini->current_cmd = NULL;
	if (lexer->token_type == PIPE)
	{
		mini->new_cmd = malloc(sizeof(t_parser_commands));
		if (mini->new_cmd == NULL)
			exit(1);
		init_new_cmd(mini);
		if (mini->cmd_list == NULL)
			mini->cmd_list = mini->new_cmd;
		else if (mini->current_cmd != NULL)
		{
			mini->current_cmd->next = mini->new_cmd;
			mini->new_cmd->prev = mini->current_cmd;
		}
		mini->current_cmd = mini->new_cmd;
	}
}
void	redirections_handler(t_lexer *lexer, t_mini *mini)
{
	t_lexer *new_redirection;
	t_lexer *tmp;
	if (lexer->token_type == REDIREC_IN || lexer->token_type == REDIREC_OUT
		|| lexer->token_type == HEREDOC || lexer->token_type == APPEND)
	{
		new_redirection = malloc(sizeof(t_lexer));
		new_redirection->str = ft_strdup(lexer->str);
		new_redirection->token_type = lexer->token_type;
		if (!mini->current_cmd)
			mini->current_cmd = (t_parser_commands *)new_redirection;
		else
		{
			tmp = (t_lexer *)mini->current_cmd;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_redirection;
		}
		mini->current_cmd->num_redirections++;
	}
}
