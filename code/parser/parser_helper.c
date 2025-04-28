/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:37:43 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/28 15:50:35 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	init_new_cmd(t_mini *mini)
{
	mini->new_list_element->cmd_str = NULL;
	mini->new_list_element->num_redirections = 0;
	mini->new_list_element->hd_file_name = NULL;
	mini->new_list_element->redirections = NULL;
	mini->new_list_element->next = NULL;
	mini->new_list_element->prev = NULL;
}


void	handle_heredocs(t_mini *mini)
{
	t_lexer *token_tmp;

	token_tmp = mini->token;
	if (mini->token->token_type == HEREDOC)
	{
		if (token_tmp->next)
			token_tmp = token_tmp->next;
		mini->current_list_element->hd_file_name = token_tmp->str;
	}
}

void	handle_filename(t_mini *mini)
{
	t_lexer *token_tmp;

	token_tmp = mini->token;
	if (token_tmp->token_type == WORD)
	{
		mini->filename = malloc(sizeof(t_lexer));
		if (!mini->filename)
			exit (1);
		mini->filename->str = ft_strdup(token_tmp->str);
		mini->filename->token_type = token_tmp->token_type;
		mini->filename->next = NULL;
		mini->current->next = mini->filename;
		mini->current = mini->filename;
	}
}

void	create_parser_node(t_mini *mini)
{
	if (!mini->first_list_element)
		mini->first_list_element = mini->new_list_element;
	if (mini->current_list_element)
	{
		mini->current_list_element->next = mini->new_list_element;
		mini->new_list_element->prev = mini->current_list_element;
	}
	mini->current_list_element = mini->new_list_element;
}
