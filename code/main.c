/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iheb <iheb@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:37:28 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/05 11:49:22 by iheb             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	(void)env;
	if (argc != 1 || argv[1])
	{
		ft_putendl_fd("this program should not have any argument\n", 2);
		exit(1);
	}
	minishell_loop(&mini);
	return (0);
}

void	minishell_loop(t_mini *mini)
{
	char				*str;
	t_lexer				*lex;
	t_parser_commands	*pars;
	while (1)
	{
		str = readline("Minishell: ");
		if (!str)
			break ;
		quotes_loop(&str, mini);
		lex = lexer(str);
		// print_list(lex);
		if (error_handling(lex) == 1)
		{
			pars = parser(lex, mini);
			if (pars)
			{
				builtin(lex);
				free_parser_list(pars);
			}
		}
		// print_parser_list(pars);
		add_history(str);
		free_all(str, lex);
	}
}
