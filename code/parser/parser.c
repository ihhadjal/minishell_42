/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:18:17 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/28 18:40:23 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

t_parser_commands	*parser(t_lexer *lexer, t_mini *mini)
{
	mini->first_list_element = NULL;
	mini->current_list_element = NULL;
	mini->current_token = lexer;
	while (mini->current_token)
	{
		mini->new_list_element = malloc(sizeof(t_parser_commands));
		init_new_cmd(mini);
		mini->head = NULL;
		mini->current = NULL;
		while (mini->current_token && mini->current_token->token_type != PIPE)
		{
			mini->processed_token = redirections_and_commands_handler(mini);
			if (!mini->processed_token)
				return (NULL);
			mini->current_token = mini->processed_token->next;
		}
		mini->new_list_element->redirections = mini->head;
		create_parser_node(mini);
		if (mini->current_token && mini->current_token->token_type == PIPE)
			mini->current_token = mini->current_token->next;
	}
	free(mini->new_list_element);
	free(mini->new_array);
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
			printf("minishell: syntax error near unexpected token 'newline'\n");
		if (next_token)
			mini->new_redirec_element->str = ft_strdup(next_token->str);
		mini->new_list_element->num_redirections++;
		return (next_token);
	}
	else if (mini->token->token_type == WORD)
	{
		mini->new_list_element->cmd_str = add_string_to_array(mini->new_list_element->cmd_str,
				mini->token->str, mini);
		return (mini->token);
	}
	return (mini->token);
}
void	create_redirection_node(t_mini *mini)
{
	mini->new_redirec_element = malloc(sizeof(t_lexer));
	if (!mini->new_redirec_element)
		exit(1);
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
		exit(1);
	mini->i = 0;
	if (array)
	{
		while (array[mini->i])
		{
			mini->new_array[mini->i] = array[mini->i];
			mini->i++;
		}
	}
	mini->array_temp = ft_strdup(str);
	mini->new_array[mini->i] = mini->array_temp;
	free(mini->array_temp);
	mini->new_array[mini->i + 1] = NULL;
	free(array);
	return (mini->new_array);
}
