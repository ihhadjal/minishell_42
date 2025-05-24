/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:57:06 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/24 14:24:01 by ihhadjal         ###   ########.fr       */
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

int	export_with_arguments(t_environnement *mini_env, t_lexer *builtin)
{
	t_environnement	*env_argument;
	t_environnement	*current;

	current = mini_env;
	while (builtin)
	{
		if (builtin->next && ft_strchr(builtin->next->str, '=')
			&& !ft_isdigit(builtin->next->str[0]) && ft_symbols(builtin->next->str) == 0 && builtin->next->str && builtin->next->str[0] != '=')
		{
			builtin = builtin->next;
			env_argument = add_argument_to_env(builtin);
			if (env_argument && update_env(env_argument, mini_env) == 0)
			{
				while (current && current->next)
					current = current->next;
				if (current)
					current->next = env_argument;
				else
					mini_env = env_argument;
			}
		}
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
int	ft_symbols(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 33 && str[i] <= 47)|| (str[i] >= 58 && str[i] <= 60)
			|| (str[i] >= 91 && str[i] <= 94) || (str[i] == 96) || (str[i] >= 123
			&& str[i] <= 126) || (str[i] >= 62 && str[i] <= 63))
			return (1);
		i++;
	}
	return (0);
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
t_environnement	*add_argument_to_env(t_lexer *builtin)
{
	t_environnement	*new_argument_node;
	char			*temp;
	char			*equal_sign;
	int				name_lenght;

	new_argument_node = malloc(sizeof(t_environnement));
	if (!new_argument_node)
		return (NULL);
	equal_sign = ft_strchr(builtin->str, '=');
	if (equal_sign)
	{
		name_lenght = equal_sign - builtin->str + 1;
		temp = ft_substr(builtin->str, 0, name_lenght);
		new_argument_node->variable_name = ft_strdup(temp);
		free(temp);
		new_argument_node->variable_value = ft_strdup(equal_sign + 1);
	}
	else
	{
		free(new_argument_node);
		return (NULL);
	}
	new_argument_node->next = NULL;
	return (new_argument_node);
}
