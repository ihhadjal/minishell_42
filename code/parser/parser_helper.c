/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:37:43 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/21 18:36:35 by ihhadjal         ###   ########.fr       */
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
	if (mini->token->token_type == HEREDOC)
	{
		if (mini->token->next)
			mini->token = mini->token->next;
		else
			printf("syntax error: add a heredoc filename\n");
		mini->current_list_element->hd_file_name = mini->token->str;
	}
}

void	handle_filename(t_mini *mini)
{
	if (mini->token->token_type == WORD)
	{
		mini->new_redirec_element->str = ft_strdup(mini->token->str);
		mini->token = mini->token->next;
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
