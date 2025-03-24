/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:37:28 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/03/24 12:25:42 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../resources/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_lexer	token;
	(void)env;
	if (argc != 1 || argv[1])
	{
		ft_printf("this program should not have any argument\n");
		exit(1);
	}
	minishell_loop(&token);
	return (0);
}