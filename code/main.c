/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:37:28 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/24 14:45:18 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	t_environnement *mini_env;
	t_expander		exp;

	mini.last_exit_status = 0;
	if (argc != 1 || argv[1])
	{
		ft_putendl_fd("this program should not have any argument\n", 2);
		exit(1);
	}
	else
	{
		mini_env = get_env(env);
		minishell_loop(&mini, mini_env, &exp);
	}
	return (0);
}

void	minishell_loop(t_mini *mini, t_environnement *mini_env, t_expander *exp)
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
				expand_commands(lex, mini_env, exp, mini);
				mini->last_exit_status = builtin(lex, mini_env);
				free_parser_list(pars);
			}
		}
		add_history(str);
		free_all(str, lex);
	}
}

