/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:09:23 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/03/24 10:47:03 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/minishell.h"

void	minishell_loop(t_lexer *lex)
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
		tokenizer(str, lex);
		add_history(str);
		free(str);
	}
}

t_lexer	*tokenizer(char *str, t_lexer *lex)
{
	t_lexer *list;
	int i;
	
	i = 0;
	list = NULL;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else if (str[i] == '"')
		{
			
		}
	}
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
