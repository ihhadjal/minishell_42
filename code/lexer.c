/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:09:23 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/03/26 14:08:49 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/minishell.h"

t_lexer	*lexer(char *str)
{
	int		i;
	t_lexer	*list;
	t_lexer	*token;

	i = 0;
	list = NULL;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '\0')
			break ;
		token = get_token(&str[i]);
		if (!token)
		{
			free_lexer_list(list);
			exit(1);
		}
		add_token_to_list(&list, token);
		i += ft_strlen(token->str);
	}
	return (list);
}

t_lexer	*get_token(char *str)
{
	t_lexer	*token;

	token = malloc(sizeof(t_lexer));
	if (!token)
		return (NULL);
	token->next = NULL;
	token->str = NULL;
	token->token_type = WORD;
	pipe_token(str, token);
	redirec_in_token(str, token);
	redirec_out_token(str, token);
	if (token->str == NULL)
		token = get_word(str, token);
	return (token);
}

t_lexer	*get_word(char *str, t_lexer *token)
{
	int	i;
	int	quote;

	i = 0;
	while (str[i] && !is_sep(str[i]))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				i++;
		}
		else
			i++;
	}
	token->str = ft_substr(str, 0, i);
	token->token_type = WORD;
	return (token);
}
int	is_sep(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}
int	check_quotes(char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] == '"')
			double_quote++;
		else if (str[i] == '\'')
			single_quote++;
		i++;
	}
	if (double_quote % 2 != 0 || single_quote % 2 != 0)
		return (0);
	return (1);
}
