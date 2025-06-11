/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:04:20 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/11 16:41:32 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	check_redirections(t_lexer *lex)
{
	if (lex->next->token_type == REDIREC_OUT)
		ft_putendl_fd("syntax error near unexpected token `>'", 2);
	else
		ft_putendl_fd("syntax error near unexpected token `>>'", 2);
	return (0);
}

void	init_list(t_mini *mini, t_lexer *lexer)
{
	mini->first_list_element = NULL;
	mini->current_list_element = NULL;
	mini->current_token = lexer;
}

void	free_env(t_environnement *env)
{
	t_environnement	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->variable_name);
		free(env->variable_value);
		free(env);
		env = tmp;
	}
}
