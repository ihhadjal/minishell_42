/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iheb <iheb@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:57:06 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/21 10:28:29 by iheb             ###   ########.fr       */
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

void	export_with_arguments(t_environnement *mini_env, t_lexer *builtin)
{
	t_environnement	*env_argument;
	t_environnement	*current;

	current = mini_env;
	while (builtin)
	{
		if (builtin->next && ft_strchr(builtin->next->str, '='))
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
		builtin = builtin->next;
	}
}

int	update_env(t_environnement  *env_argument, t_environnement *mini_env)
{
	t_environnement *current;

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
		free (temp);
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
