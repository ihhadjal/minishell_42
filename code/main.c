/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:37:28 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/23 21:45:18 by ihhadjal         ###   ########.fr       */
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
		builtin(lex);
		// print_list(lex);
		pars = parser(lex, mini);
		// print_parser_list(pars);
		if (!pars)
			printf("eror");
		add_history(str);
		free_all(str, lex);
	}
}
void	print_parser_list(t_parser_commands *head)
{
	int	i;
	t_lexer *redir;

	while (head)
	{
		printf("=== Command ===\n");

		// Print command arguments
		if (head->cmd_str)
		{
			i = 0;
			while (head->cmd_str[i])
			{
				printf("Arg[%d]: %s\n", i, head->cmd_str[i]);
				i++;
			}
		}
		else
			printf("No command\n");

		// Print redirections
		redir = head->redirections;
		while (redir)
		{
			printf("Redirection type: %d, file: %s\n", redir->token_type,
				redir->str ? redir->str : "(null)");
			redir = redir->next;
		}

		// Print heredoc file name if any
		if (head->hd_file_name)
			printf("Heredoc file: %s\n", head->hd_file_name);

		printf("================\n");

		head = head->next;
	}
}