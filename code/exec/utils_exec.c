/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:49:14 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/11 15:46:55 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

char	**env_to_array(t_environnement *mini_env)
{
	char			**env_array;
	t_environnement	*current;
	int				count;
	int				i;

	count = count_env_vars(mini_env);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = mini_env;
	i = 0;
	while (current && i < count)
	{
		env_array[i] = create_env_string(current);
		if (!env_array[i])
		{
			free_env_array_partial(env_array, i);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

int	count_env_vars(t_environnement *mini_env)
{
	t_environnement	*current;
	int				count;

	count = 0;
	current = mini_env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	*create_env_string(t_environnement *env_var)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(env_var->variable_name, env_var->variable_value);
	if (!temp)
		return (NULL);
	result = ft_strdup(temp);
	free(temp);
	return (result);
}

void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

void	free_env_array_partial(char **env_array, int count)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (i < count)
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}
