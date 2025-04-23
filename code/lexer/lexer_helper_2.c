/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakambou <fakambou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:01:42 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/23 17:53:53 by fakambou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	builtin_tokens2(char *str, t_lexer *lexer)
{
	if (!ft_strncmp(str, "env", 3) && is_sep(str[3]))
	{
		lexer->str = ft_strdup("env");
		lexer->token_type = ENV;
	}
	else if (!ft_strncmp(str, "exit", 4) && is_sep(str[4]))
	{
		lexer->str = ft_strdup("exit");
		lexer->token_type = EXIT;
	}
	// else if (!ft_strncmp(str, "echo -n", 7) && is_sep(str[7]))
	// {
	// 	lexer->str = ft_strdup("echo -n");
	// 	lexer->token_type = ECHO2;
	// }
}