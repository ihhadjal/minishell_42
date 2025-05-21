/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iheb <iheb@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:27:55 by iheb              #+#    #+#             */
/*   Updated: 2025/05/21 10:28:32 by iheb             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int		check_if_builtin(t_lexer *current, int command_found)
{
	if (current->token_type == ECHO || 
		current->token_type == CD ||
		current->token_type == PWD ||
		current->token_type == EXIT ||
		current->token_type == EXPORT ||
		current->token_type == ENV ||
		current->token_type == UNSET)
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