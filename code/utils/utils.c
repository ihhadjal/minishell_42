/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:57:56 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/27 15:40:58 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	quotes_loop(char **str, t_mini *mini)
{
	while (!check_quotes(*str))
	{
		mini->tmp = *str;
		mini->str1 = readline("> ");
		*str = ft_strjoin(*str, mini->str1);
		free(mini->str1);
		free(mini->tmp);
	}
}

void	builtin_tokens(char *str, t_lexer *lexer)
{
	if (!ft_strncmp(str, "echo", 4) && is_sep(str[4]))
	{
		lexer->str = ft_strdup("echo");
		lexer->token_type = ECHO;
	}
	else if (!ft_strncmp(str, "cd", 2) && is_sep(str[2]))
	{
		lexer->str = ft_strdup("cd");
		lexer->token_type = CD;
	}
	else if (!ft_strncmp(str, "pwd", 3) && is_sep(str[3]))
	{
		lexer->str = ft_strdup("pwd");
		lexer->token_type = PWD;
	}
	else if (!ft_strncmp(str, "export", 6) && is_sep(str[6]))
	{
		lexer->str = ft_strdup("export");
		lexer->token_type = EXPORT;
	}
	else if (!ft_strncmp(str, "unset", 5) && is_sep(str[5]))
	{
		lexer->str = ft_strdup("unset");
		lexer->token_type = UNSET;
	}
}

void	free_all(char *str, t_lexer *lex)
{
	free(str);
	free_lexer_list(lex);
}

void	free_node(char *var_name, t_environnement *current)
{
	free(var_name);
	free(current->variable_name);
	free(current->variable_value);
	free(current);
}

int	dispatch_builtin(t_lexer *current, t_environnement *mini_env, t_mini *mini)
{
	if (current->token_type == ECHO)
		return (put_echo(current, mini));
	else if (current->token_type == CD)
		return (cd(current));
	else if (current->token_type == PWD)
		return (get_pwd());
	else if (current->token_type == EXIT)
		ft_exit(current);
	else if (current->token_type == EXPORT)
		return (export_builtin(current, mini_env));
	else if (current->token_type == ENV)
	{
		print_env(mini_env);
		return (0);
	}
	else if (current->token_type == UNSET)
		return (handle_unset_builtin(current, mini_env));
	return (1);
}
