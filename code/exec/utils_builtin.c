/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:57:53 by fakambou          #+#    #+#             */
/*   Updated: 2025/05/27 15:18:30 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

t_environnement	*get_env(char **env)
{
	int				i;
	t_environnement	*head;
	t_environnement	*current;
	t_environnement	*mini_env;

	i = 0;
	head = NULL;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			mini_env = malloc(sizeof(t_environnement));
			mini_env->variable_name = ft_substr(env[i], 0, ft_strchr(env[i],
						'=') - env[i] + 1);
			mini_env->variable_value = ft_strdup(ft_strchr(env[i], '=') + 1);
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
	int				exit_status;

	exit_status = 0;
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
		exit_status = export_with_arguments(mini_env, builtin);
	return (exit_status);
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
				name_swap(current, temp_name);
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
