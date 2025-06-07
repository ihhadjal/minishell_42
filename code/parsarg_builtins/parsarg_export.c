/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsarg_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:00:17 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/07 18:42:17 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	parsarg_export(char **str, t_environnement *mini_env)
{
	t_environnement	*env_copy;
	t_environnement	*current;
	t_environnement	*temp;
	int				exit_status;

	exit_status = 0;
	if (!str[1])
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
	else
		exit_status = parsarg_export_with_arguments(mini_env, str);
	return (exit_status);
}

int	parsarg_export_with_arguments(t_environnement *mini_env, char **str)
{
	int	result;
	int	i;

	i = 1;
	while (str[i])
	{
		result = parsarg_validate(str[i], mini_env);
		if (result != 0)
			return (result);
		i++;
	}
	return (0);
}

int	parsarg_validate(char *str, t_environnement *mini_env)
{
	if (parsarg_valid_id(str))
		return (parsarg_valid_export(str, mini_env));
	else
	{
		ft_putstr_fd("export : ", 2);
		print_error(str, ": not a valid identifier");
		return (1);
	}
}

int	parsarg_valid_id(char *str)
{
	char	*equal_sign;
	int		name_lenght;
	char	*tmp;
	char	*variable_name;

	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		return (0);
	name_lenght = equal_sign - str + 1;
	tmp = ft_substr(str, 0, name_lenght);
	variable_name = tmp;
	if (!ft_isdigit(str[0]) && ft_symbols(variable_name) == 0 && str
		&& str[0] != '=')
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	parsarg_valid_export(char *str, t_environnement *mini_env)
{
	t_environnement	*env_argument;

	env_argument = parsadd_argument_to_env(str);
	if (env_argument && parsupdate_env(env_argument, mini_env) == 0)
	{
		add_to_env_list(env_argument, mini_env);
		return (0);
	}
	return (0);
}
