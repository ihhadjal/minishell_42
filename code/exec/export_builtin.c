/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:28:16 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/27 19:33:06 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	is_valid_identifier(char *str)
{
	char	*equal_sign;
	int		name_lenght;

	equal_sign = ft_strchr(str, '=');
	name_lenght = equal_sign - str + 1;
	if (!ft_isdigit(str[0]) && ft_symbols(ft_substr(str, 0, name_lenght)) == 0
		&& str && str[0] != '=')
		return (1);
	return (0);
}

void	add_to_env_list(t_environnement *env_argument,
		t_environnement *mini_env)
{
	t_environnement	*current;

	current = mini_env;
	while (current && current->next)
		current = current->next;
	if (current)
		current->next = env_argument;
	else
		mini_env = env_argument;
}

int	process_valid_export(t_lexer *builtin, t_environnement *mini_env)
{
	t_environnement	*env_argument;

	env_argument = add_argument_to_env(builtin);
	if (env_argument && update_env(env_argument, mini_env) == 0)
	{
		add_to_env_list(env_argument, mini_env);
		return (0);
	}
	return (0);
}

int	validate_and_add_export(t_lexer *builtin, t_environnement *mini_env)
{
	if (is_valid_identifier(builtin->str))
		return (process_valid_export(builtin, mini_env));
	else
	{
		ft_putstr_fd("export : ", 2);
		print_error(builtin->str, ": not a valid identifier");
		return (1);
	}
}

int	export_with_arguments(t_environnement *mini_env, t_lexer *builtin)
{
	int	result;

	while (builtin)
	{
		if (builtin->next)
		{
			result = validate_and_add_export(builtin->next, mini_env);
			if (result != 0)
				return (result);
		}
		builtin = builtin->next;
	}
	return (0);
}
