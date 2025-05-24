/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:57:53 by fakambou          #+#    #+#             */
/*   Updated: 2025/05/24 14:24:08 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

t_environnement	*get_env(char **env)
{
	int				i;
	char			*equal_sign;
	t_environnement	*head;
	t_environnement	*current;
	t_environnement	*mini_env;

	i = 0;
	head = NULL;
	while (env[i])
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)
		{
			mini_env = malloc(sizeof(t_environnement));
			mini_env->variable_name = ft_substr(env[i], 0, equal_sign - env[i]
					+ 1);
			mini_env->variable_value = ft_strdup(equal_sign + 1);
			mini_env->next = NULL;
			if (!head)
				head = mini_env;
			else
				current->next = mini_env;
			current = mini_env;
		}
		i++;
	}
	return (head);
}

int	export_builtin(t_lexer *builtin, t_environnement *mini_env)
{
	t_environnement	*env_copy;
	t_environnement	*current;
	t_environnement	*temp;

	if (builtin->token_type == EXPORT && !builtin->next)
	{
		env_copy = copy_env(mini_env);
		env_copy = env_sort(env_copy);
		current = env_copy;
		while (current)
		{
			printf("%s%s%c%s%c\n", "declare -x ", current->variable_name, '"',
				current->variable_value, '"');
			temp = current;
			free_env_variables(temp);
			current = current->next;
		}
		return (0);
	}
	else if (builtin->token_type == EXPORT && builtin->next->token_type == WORD)
		export_with_arguments(mini_env, builtin);
	return (1);
}

t_environnement	*env_sort(t_environnement *env_copy)
{
	char			*temp_name;
	char			*temp_value;
	t_environnement	*current;
	int				swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = env_copy;
		while (current->next)
		{
			if (ft_strcmp(current->variable_name,
					current->next->variable_name) > 0)
			{
				temp_name = current->variable_name;
				current->variable_name = current->next->variable_name;
				current->next->variable_name = temp_name;
				temp_value = current->variable_value;
				value_swap(current, temp_value);
				swapped = 1;
			}
			current = current->next;
		}
	}
	return (env_copy);
}

t_environnement	*copy_env(t_environnement *mini_env)
{
	t_environnement	*new_node;
	t_environnement	*head;
	t_environnement	*tmp;
	t_environnement	*current;

	current = mini_env;
	head = NULL;
	tmp = NULL;
	while (current)
	{
		new_node = malloc(sizeof(t_environnement));
		new_node->variable_name = ft_strdup(current->variable_name);
		new_node->variable_value = ft_strdup(current->variable_value);
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			tmp->next = new_node;
		tmp = new_node;
		current = current->next;
	}
	return (head);
}

void	print_env(t_environnement *mini_env)
{
	while (mini_env)
	{
		printf("%s%s\n", mini_env->variable_name, mini_env->variable_value);
		mini_env = mini_env->next;
	}
}