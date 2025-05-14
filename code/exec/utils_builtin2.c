/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:57:06 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/14 17:58:13 by ihhadjal         ###   ########.fr       */
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
void	free_env_variables(t_environnement *temp)
{
	free(temp->variable_name);
	free(temp->variable_value);
	free(temp);
}

void	export_with_arguments(t_environnement *mini_env, t_lexer *builtin)
{
	t_environnement	*env_argument;
	t_environnement	*current;

	current = mini_env;
	while (builtin)
	{
		builtin = builtin->next;
		if (builtin->token_type == EXPORT && !ft_strchr(builtin->next->str,
				'='))
			return ;
		else
		{
			env_argument = add_argument_to_env(builtin, mini_env);
			while (current->next)
				current = current->next;
			current->next = env_argument;
		}
		builtin = builtin->next;
	}
}
t_environnement	*add_argument_to_env(t_lexer *builtin,
		t_environnement *mini_env)
{
	t_environnement	*new_argument_node;
	t_environnement	*current;
	t_environnement	*head;
	t_environnement	*temp;

	current = mini_env;
	head = NULL;
	while (current)
	{
		new_argument_node = malloc(sizeof(t_environnement));
		new_argument_node->variable_name = ft_strdup(ft_substr(builtin->str, 0,
					ft_strlen(ft_strchr(builtin->str, '=') + 1)));
		new_argument_node->variable_value = ft_strdup(ft_substr(builtin->str,
					ft_strlen(ft_strchr(builtin->str, '=')),
					ft_strlen(builtin->str)));
		if (!head)
			head = new_argument_node;
		else
			temp->next = new_argument_node;
		temp = new_argument_node;
		current = current->next;
	}
	return (new_argument_node);
}
