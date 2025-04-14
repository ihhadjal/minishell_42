/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:37:28 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/14 19:12:46 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	(void)env;
	if (argc != 1 || argv[1])
	{
		ft_printf("this program should not have any argument\n");
		exit(1);
	}
	minishell_loop(&mini);
	return (0);
}

void	minishell_loop(t_mini *mini)
{
	char		*str;
	t_lexer		*lex;

	while (1)
	{
		str = readline("Minishell: ");
		if (!str)
			break ;
		quotes_loop(&str, mini);
		lex = lexer(str);
		add_history(str);
		free_all(str, lex);
	}
}
