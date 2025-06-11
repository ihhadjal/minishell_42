/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsarg_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:11:00 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/11 15:49:36 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	parsarg_unset(char **str, t_environnement *mini_env)
{
	int	i;

	if (ft_strcmp(str[0], "unset") == 0)
	{
		i = 1;
		while (str[i])
		{
			parsdelete_node(str[i], &mini_env);
			i++;
		}
		return (0);
	}
	else
		return (1);
}

void	parsdelete_node(char *var_to_unset, t_environnement **mini_env)
{
	t_environnement	*current;
	t_environnement	*prev;
	int				var_len;
	char			*var_name;

	current = *mini_env;
	prev = NULL;
	while (current)
	{
		var_len = ft_strlen(current->variable_name);
		var_name = ft_substr(current->variable_name, 0, var_len - 1);
		if (var_name && ft_strcmp(var_name, var_to_unset) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*mini_env = current->next;
			parsfree_node(var_name, current);
			return ;
		}
		free(var_name);
		prev = current;
		current = current->next;
	}
}

void	parsfree_node(char *var_name, t_environnement *node)
{
	free(var_name);
	free(node->variable_name);
	free(node->variable_value);
	free(node);
}
