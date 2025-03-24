/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:09:23 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/03/24 12:27:55 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/minishell.h"

void	minishell_loop(t_lexer *token)
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
		lexer(str, token);
		add_history(str);
		free(str);
	}
}

t_lexer	*lexer(char *str, t_lexer *token)
{
	t_lexer	*list;
	t_lexer	*get_token;
	int		i;

	list = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		get_token = tokenizer(str, token);
		
	}
	return (list);
}
void	init_token(t_lexer *token)
{
	token = malloc(sizeof(t_lexer));
	token->next = NULL;
	token->str = NULL;
	token->token_type = WORD;
}
t_lexer	*tokenizer(char *str, t_lexer *token)
{
	int	i;

	i = 0;
	init_token(token);
	while (str[i])
	{
		if (str[i] == '|')
		{
			token->token_type = PIPE;
			token->str = ft_strdup("|");
		}
		else if (str[i] == '>')
		{
			if (str[i + 1] == '>')
			{
				token->token_type = APPEND;
				token->str = ft_strdup(">>");
			}
			token->token_type = REDIREC_OUT;
			token->str = ft_strdup(">");
		}
		else if (str[i] == '<')
		{
			if (str[i + 1] == '<')
			{
				token->token_type = HEREDOC;
				token->str = ft_strdup("<<");
			}
			token->token_type = REDIREC_IN;
			token->str = ft_strdup("<");
		}
	}
	return (token);
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
