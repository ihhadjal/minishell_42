/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:18:17 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/21 19:01:09 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

t_parser_commands	*parser(t_lexer *lexer, t_mini *mini)
{
	mini->first_list_element = NULL;
	mini->current_list_element = NULL;
	mini->head = NULL;
	mini->current = NULL;
	mini->current_token = lexer;
	while (mini->current_token)
	{
		mini->new_list_element = malloc(sizeof(t_parser_commands));
		if (!mini->new_list_element)
			exit(1);
		init_new_cmd(mini);
		create_parser_node(mini);
		if (mini->current_token->token_type == PIPE)
			mini->current_token = mini->current_token->next;
		mini->current_token = redirections_and_commands_handler(mini);
		if (mini->current_token)
			mini->current_token = mini->current_token->next;
	}
	return (mini->first_list_element);
}

t_lexer	*redirections_and_commands_handler(t_mini *mini)
{
	mini->token = mini->current_token;
	if (mini->token->token_type == REDIREC_IN
		|| mini->token->token_type == REDIREC_OUT
		|| mini->token->token_type == APPEND
		|| mini->token->token_type == HEREDOC)
	{
		create_redirection_node(mini->head, mini->current, mini);
		mini->current_list_element->num_redirections++;
		handle_heredocs(mini);
		if (mini->token->next)
			mini->token = mini->token->next;
		else
			printf("syntax error: add a filename\n");
		handle_filename(mini);
	}
	else
		handle_command_arguments(mini);
	mini->current_list_element->redirections = mini->head;
	return (mini->token);
}
void	handle_commands_arguments(t_mini *mini)
{
	
}
void	create_redirection_node(t_lexer *head, t_lexer *current, t_mini *mini)
{
	mini->new_redirec_element = malloc(sizeof(t_lexer));
	if (!mini->new_redirec_element)
		exit(1);
	if (!head)
	{
		head = mini->new_redirec_element;
		current = head;
	}
	else
	{
		current->next = mini->new_redirec_element;
		current = mini->new_redirec_element;
	}
	mini->new_redirec_element->str = ft_strdup(mini->token->str);
	mini->new_redirec_element->token_type = mini->token->token_type;
	mini->new_redirec_element->next = NULL;
}
