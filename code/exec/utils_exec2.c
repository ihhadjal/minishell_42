/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:49:49 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/10 12:50:00 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

char	*get_env_value(char *var_name, t_environnement *mini_env)
{
	t_environnement	*current;
	char			*name_with_equal;
	int				name_len;

	name_len = ft_strlen(var_name);
	name_with_equal = malloc(name_len + 2);
	if (!name_with_equal)
		return (NULL);
	ft_strcpy(name_with_equal, var_name);
	ft_strcat(name_with_equal, "=");
	current = mini_env;
	while (current)
	{
		if (ft_strncmp(current->variable_name, name_with_equal, name_len
				+ 1) == 0)
		{
			free(name_with_equal);
			return (current->variable_value);
		}
		current = current->next;
	}
	free(name_with_equal);
	return (NULL);
}

char	*create_full_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

void	free_split_array(char **array)
{
	int i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}