/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:27:55 by iheb              #+#    #+#             */
/*   Updated: 2025/05/27 20:08:06 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	check_if_builtin(t_lexer *current, int command_found)
{
	if (current->token_type == ECHO || current->token_type == CD
		|| current->token_type == PWD || current->token_type == EXIT
		|| current->token_type == EXPORT || current->token_type == ENV
		|| current->token_type == UNSET)
	{
		if (command_found)
			command_found = 1;
		return (1);
	}
	return (0);
}

void	free_env_variables(t_environnement *temp)
{
	free(temp->variable_name);
	free(temp->variable_value);
	free(temp);
}

void	print_error(char *str1, char *str)
{
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(str, 2);
}

void	print_env(t_environnement *mini_env)
{
	while (mini_env)
	{
		printf("%s%s\n", mini_env->variable_name, mini_env->variable_value);
		mini_env = mini_env->next;
	}
}
