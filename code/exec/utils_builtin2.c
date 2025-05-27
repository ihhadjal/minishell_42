/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:57:06 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/27 15:35:42 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (0);
		i++;
	}
	return (1);
}

void	value_swap(t_environnement *current, char *temp_value)
{
	current->variable_value = current->next->variable_value;
	current->next->variable_value = temp_value;
}

int	handle_valid_argument(t_lexer *builtin, t_environnement **mini_env)
{
	t_environnement	*env_argument;
	t_environnement	*current;

	builtin = builtin->next;
	env_argument = add_argument_to_env(builtin);
	if (env_argument && update_env(env_argument, *mini_env) == 0)
	{
		current = *mini_env;
		while (current && current->next)
			current = current->next;
		if (current)
			current->next = env_argument;
		else
			*mini_env = env_argument;
	}
	return (0);
}

int	export_with_arguments(t_environnement *mini_env, t_lexer *builtin)
{
	int		name_length;
	char	*equal_sign;

	if (!builtin || !builtin->next || !builtin->next->str)
		return (1);
	equal_sign = ft_strchr(builtin->next->str, '=');
	if (!equal_sign)
		return (1);
	name_length = equal_sign - builtin->next->str + 1;
	while (builtin)
	{
		if (builtin->next && is_valid_export_argument(builtin->next->str,
				name_length))
			return (handle_valid_argument(builtin, &mini_env));
		else
		{
			ft_putstr_fd("export : ", 2);
			print_error(builtin->next->str, ": not a valid identifier");
			return (1);
		}
		builtin = builtin->next;
	}
	return (1);
}

int	update_env(t_environnement *env_argument, t_environnement *mini_env)
{
	t_environnement	*current;

	current = mini_env;
	while (current)
	{
		if (ft_strcmp(current->variable_name, env_argument->variable_name) == 0)
		{
			current->variable_value = ft_strdup(env_argument->variable_value);
			return (1);
		}
		current = current->next;
	}
	return (0);
}
