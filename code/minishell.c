/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:09:23 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/03/26 13:45:52 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/minishell.h"

void	minishell_loop(void)
{
	char	*str;
	char	*str1;
	t_lexer	*lex;

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
		lex = lexer(str);
		if (!lex)
			return ;
		if (lex)
			print_tokens(lex);
		add_history(str);
		free(str);
		free_lexer_list(lex);
	}
}

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
	printf("%s\n", token->str);
	return (token);
}

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

void	print_tokens(t_lexer *head)
{
	t_lexer	*current;
	char	*token_names[] = {"WORD", "PIPE", "REDIREC_IN", "REDIREC_OUT",
			"APPEND", "HEREDOC"};

	current = head;
	while (current)
	{
		printf("Token: %s, Type: %s\n", current->str,
			token_names[current->token_type]);
		current = current->next;
	}
}
