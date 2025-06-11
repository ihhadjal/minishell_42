/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:18:17 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/11 16:17:06 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	skip_empty_tokens(t_mini *mini)
{
	while (mini->current_token && mini->current_token->str
		&& ft_strlen(mini->current_token->str) == 0)
	{
		mini->current_token = mini->current_token->next;
	}
}

t_parser_commands	*parser(t_lexer *lexer, t_mini *mini)
{
	init_list(mini, lexer);
	while (mini->current_token)
	{
		skip_empty_tokens(mini);
		mini->new_list_element = malloc(sizeof(t_parser_commands));
		init_new_cmd(mini);
		mini->head = NULL;
		mini->current = NULL;
		while (mini->current_token && mini->current_token->token_type != PIPE)
		{
			mini->processed_token = redirections_and_commands_handler(mini);
			if (!mini->processed_token)
			{
				free(mini->new_list_element);
				return (NULL);
			}
			mini->current_token = mini->processed_token->next;
		}
		mini->new_list_element->redirections = mini->head;
		create_parser_node(mini);
		if (mini->current_token && mini->current_token->token_type == PIPE)
			mini->current_token = mini->current_token->next;
	}
	return (mini->first_list_element);
}

t_lexer	*redirections_and_commands_handler(t_mini *mini)
{
	t_lexer	*next_token;

	mini->token = mini->current_token;
	if (mini->token->token_type == REDIREC_IN
		|| mini->token->token_type == REDIREC_OUT
		|| mini->token->token_type == APPEND
		|| mini->token->token_type == HEREDOC)
	{
		create_redirection_node(mini);
		next_token = mini->token->next;
		if (!next_token || next_token->token_type != WORD)
			redirection_cleanup(mini);
		if (next_token && mini->new_redirec_element)
			mini->new_redirec_element->str = ft_strdup(next_token->str);
		mini->new_list_element->num_redirections++;
		return (next_token);
	}
	else if (mini->token->token_type == WORD)
	{
		mini->new_list_element->cmd_str = add_string_to_array(
				mini->new_list_element->cmd_str, mini->token->str, mini);
		return (mini->token);
	}
	return (mini->token);
}

void	create_redirection_node(t_mini *mini)
{
	mini->new_redirec_element = malloc(sizeof(t_lexer));
	if (!mini->new_redirec_element)
		return ;
	mini->new_redirec_element->str = NULL;
	mini->new_redirec_element->token_type = mini->token->token_type;
	mini->new_redirec_element->next = NULL;
	if (!mini->head)
	{
		mini->head = mini->new_redirec_element;
		mini->current = mini->head;
	}
	else
	{
		mini->current->next = mini->new_redirec_element;
		mini->current = mini->new_redirec_element;
	}
}

char	**add_string_to_array(char **array, char *str, t_mini *mini)
{
	mini->i = 0;
	if (array)
	{
		while (array[mini->i])
			mini->i++;
	}
	mini->new_array = malloc(sizeof(char *) * (mini->i + 2));
	if (!mini->new_array)
		return (NULL);
	mini->i = 0;
	if (array)
	{
		while (array[mini->i])
		{
			mini->new_array[mini->i] = array[mini->i];
			mini->i++;
		}
	}
	mini->new_array[mini->i] = ft_strdup(str);
	mini->new_array[mini->i + 1] = NULL;
	if (array)
		free(array);
	return (mini->new_array);
}
