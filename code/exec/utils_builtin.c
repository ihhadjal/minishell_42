/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakambou <fakambou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:57:53 by fakambou          #+#    #+#             */
/*   Updated: 2025/05/13 18:12:24 by fakambou         ###   ########.fr       */
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

void	export_builtin(t_lexer *builtin, t_environnement *mini_env)
{
	(void)mini_env;
	if (builtin->token_type == EXPORT && !builtin->next)
		print_env(mini_env);
}

void	print_env(t_environnement *mini_env)
{
	while (mini_env)
	{
		printf("%s%s%c%s\n", "declare -x ", mini_env->variable_name, '=', mini_env->variable_value);
		mini_env = mini_env->next;
	}
}
