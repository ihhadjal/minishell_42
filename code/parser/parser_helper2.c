/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:18:52 by iheb              #+#    #+#             */
/*   Updated: 2025/05/27 15:02:14 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	free_redirections_list(t_lexer *list)
{
	t_lexer	*current;
	t_lexer	*next;

	current = list;
	while (current)
	{
		next = current->next;
		if (current->str)
			free(current->str);
		free(current);
		current = next;
	}
}

void	free_parser_list(t_parser_commands *list)
{
	t_parser_commands	*current;
	t_parser_commands	*next;
	int					i;

	current = list;
	while (current)
	{
		next = current->next;
		if (current->redirections)
			free_redirections_list(current->redirections);
		if (current->cmd_str)
		{
			i = 0;
			while (current->cmd_str[i])
			{
				free(current->cmd_str[i]);
				i++;
			}
			free(current->cmd_str);
		}
		free(current);
		current = next;
	}
}

void	redirection_cleanup(t_mini *mini)
{
	t_lexer	*temp;

	ft_putendl_fd("syntax error near unexpected token `newline'", 2);
	if (mini->head == mini->new_redirec_element)
		mini->head = NULL;
	else if (mini->current == mini->new_redirec_element)
	{
		temp = mini->head;
		while (temp && temp->next != mini->new_redirec_element)
			temp = temp->next;
		temp->next = NULL;
	}
	free(mini->new_redirec_element);
	mini->new_redirec_element = NULL;
	return ;
}
