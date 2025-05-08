/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:57:53 by fakambou          #+#    #+#             */
/*   Updated: 2025/05/08 15:59:16 by ihhadjal         ###   ########.fr       */
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

t_environnement	*get_env(char **env)
{
	int				i;
	char			*equal_sign;
	t_environnement *head;
	t_environnement *current;
	t_environnement *env_container;
	i = 0;
	head = NULL;
	while (env[i])
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)
		{
			env_container = malloc(sizeof(t_environnement));
			env_container->variable_name = ft_substr(env[i], 0, equal_sign - env[i]);
			env_container->variable_value = ft_strdup(equal_sign + 1);
            env_container->next = NULL;
			if (!head)
				head = env_container;
			else
				current->next = env_container;
			current = env_container;
		}
		i++;
	}
	return (head);
}

void	init_env_container(t_environnement *env_container)
{
	env_container->is_exported = false;
	env_container->next = NULL;
	env_container->variable_name = NULL;
	env_container->variable_value = NULL;
}