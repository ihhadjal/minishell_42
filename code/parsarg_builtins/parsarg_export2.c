/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsarg_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:41:49 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/07 18:42:14 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

t_environnement	*parsadd_argument_to_env(char *str)
{
	t_environnement	*new_argument_node;
	char			*temp;
	char			*equal_sign;
	int				name_lenght;

	new_argument_node = malloc(sizeof(t_environnement));
	if (!new_argument_node)
		return (NULL);
	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
	{
		name_lenght = equal_sign - str + 1;
		temp = ft_substr(str, 0, name_lenght);
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

int	parsupdate_env(t_environnement *env_argument, t_environnement *mini_env)
{
	t_environnement *current;

	current = mini_env;
	while (current)
	{
		if (ft_strcmp(current->variable_name, env_argument->variable_name) == 0)
		{
			free(current->variable_value);
			current->variable_value = ft_strdup(env_argument->variable_value);
			return (1);
		}
		current = current->next;
	}
	return (0);
}