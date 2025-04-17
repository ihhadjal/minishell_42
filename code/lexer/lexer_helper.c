/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:47:05 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/17 10:10:38 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	pipe_token(char *str, t_lexer *token)
{
	if (str[0] == '|')
	{
		token->str = ft_strdup("|");
		token->token_type = PIPE;
		return (0);
	}
	return (1);
}

int	redirec_out_token(char *str, t_lexer *token)
{
	if (str[0] == '>')
	{
		if (str[1] == '>')
		{
			token->str = ft_strdup(">>");
			token->token_type = APPEND;
			return (0);
		}
		else
		{
			token->str = ft_strdup(">");
			token->token_type = REDIREC_OUT;
			return (0);
		}
	}
	return (1);
}

int	redirec_in_token(char *str, t_lexer *token)
{
	if (str[0] == '<')
	{
		if (str[1] == '<')
		{
			token->str = ft_strdup("<<");
			token->token_type = HEREDOC;
			return (0);
		}
		else
		{
			token->str = ft_strdup("<");
			token->token_type = REDIREC_IN;
			return (0);
		}
	}
	return (1);
}
void	free_lexer_list(t_lexer *list)
{
	t_lexer	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->str);
		free(list);
		list = tmp;
	}
}

void	add_token_to_list(t_lexer **list, t_lexer *token)
{
	t_lexer	*tmp;

	if (*list == NULL)
		*list = token;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
	}
}
