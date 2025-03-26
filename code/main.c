/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:37:28 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/03/26 14:06:04 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)env;
	if (argc != 1 || argv[1])
	{
		ft_printf("this program should not have any argument\n");
		exit(1);
	}
	minishell_loop();
	return (0);
}

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
		add_history(str);
		free(str);
		free_lexer_list(lex);
	}
}