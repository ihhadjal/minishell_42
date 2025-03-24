/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:09:23 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/03/24 11:22:59 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/minishell.h"

void	minishell_loop(void)
{
	char	*str;
	char	*str1;

	while (1)
	{
		str = readline("Minishell: ");
		if (!str)
			break ;
		while (!check_quotes(str))
		{
			str1 = readline("> ");
			str = strcat(str, str1);
			free(str1);
		}
		lexer(str);
		add_history(str);
		free(str);
	}
}

t_lexer	*lexer(char *str)
{
	t_lexer	*list;
	t_lexer	*current;
	int		i;

	list = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		current = tokenizer(&str[i], i);
		if (!current)
		{
			free_lexer_list(list);
			return NULL;
		}
		add_token_to_list(&list, current);
	}
	return (list);
}

t_lexer		*tokenizer(char	*str, int i)
{
	t_lexer	*token;
	
	token = malloc(sizeof(t_lexer));
	if (!token)
		return NULL;
	token->str = NULL;
	token->token = WORD;
	token->i = i;
	token->next = NULL;
	token->prev = NULL;
	
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
